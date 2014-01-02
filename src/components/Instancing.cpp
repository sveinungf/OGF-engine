#include "components/Instancing.h"


Instancing::Instancing(const vector<vec3>& positions) : AbstractComponent(), instancePositions(positions) {
    init();
}

Instancing::Instancing(const vector<vec3>& positions, const vector<vec3>& normals)
		: AbstractComponent(), instancePositions(positions), instanceNormals(normals) {

    init();
}

void Instancing::init() {
	std::string resourceBase(OGF_RESOURCE_DIR);

    instances = instancePositions.size();
    bytesOfInstancePositions = sizeof(vec3) * instances;
    bytesOfInstanceNormals = sizeof(vec3) * instanceNormals.size();

	cullingShader << Shader(resourceBase + "/shaders/vInstanceCulling.glsl", Shader::VERT)
			<< Shader(resourceBase + "/shaders/gInstanceCulling.glsl", Shader::GEOM);

	vector<string> varyings;
	varyings.push_back("culledPosition");

	// VAO for the culling pass
    glGenVertexArrays(1, &cullVAO);
    glBindVertexArray(cullVAO);

	// Make a query object so we can later ask how many primitives the geometry shader in the culling pass emitted
	glGenQueries(1, &cullQuery);

	// Binding a buffer as a VBO which we will use in the culling pass
	glGenBuffers(1, &cullBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cullBuffer);
	glBufferData(GL_ARRAY_BUFFER, bytesOfInstancePositions + bytesOfInstanceNormals, 0, GL_STATIC_DRAW);

	// Binding a buffer as a TFB (Transform Feedback Buffer) which we will use as a VBO when rendering
	glGenBuffers(1, &positionsTFB);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, positionsTFB);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, bytesOfInstancePositions, 0, GL_DYNAMIC_COPY);

	// Putting instance data into the VBO for the culling pass
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfInstancePositions, &instancePositions[0]);
	glVertexAttribPointer(ShaderLayout::INSTANCE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	glEnableVertexAttribArray(ShaderLayout::INSTANCE_POSITION);

	// Same as previous steps but with instance normals (above is for instance positions)
	if (bytesOfInstanceNormals > 0) {
		offset += bytesOfInstancePositions;

		varyings.push_back("culledNormal");

		glGenBuffers(1, &normalsTFB);
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, normalsTFB);
		glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, bytesOfInstanceNormals, 0, GL_DYNAMIC_COPY);

		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfInstanceNormals, &instanceNormals[0]);
		glVertexAttribPointer(ShaderLayout::INSTANCE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
		glEnableVertexAttribArray(ShaderLayout::INSTANCE_NORMAL);
		
	}

	// Let's tell the shader what shader variables to listen to
    cullingShader.setTransformFeedbackOutput(varyings);
	cullingShader << Shader::LINK;
}

void Instancing::preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView,
                           const mat4& objectToWorld) {
    cullingShader.setObjectToClip(viewToClip * worldToView * objectToWorld);
	cullingShader.setUniformVec3("objectPositiveExtent", mesh->getPositiveExtent());
	cullingShader.setUniformVec3("objectNegativeExtent", mesh->getNegativeExtent());

	// The start of the culling pass. We don't need to actually draw anything, so we can disable the fragment shader
    glEnable(GL_RASTERIZER_DISCARD);

	glBindVertexArray(cullVAO);

	// Binding the instance position TFB which the geometry shader will emit primitives to
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionsTFB);

	// And similar if we have normal
	if (bytesOfInstanceNormals > 0) {
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, normalsTFB);
	}

	// This is where it actually happens. The query object will record the amount of primitives emitted.
    glBeginTransformFeedback(GL_POINTS);
    glBeginQuery(GL_PRIMITIVES_GENERATED, cullQuery);
    glDrawArrays(GL_POINTS, 0, instances);
    glEndQuery(GL_PRIMITIVES_GENERATED);
    glEndTransformFeedback();

	// Let's enable rasterization again before rendering
    glDisable(GL_RASTERIZER_DISCARD);

	// Now we can store the value that the query object recorded, which is the amount of emitted primitives
    glGetQueryObjectiv(cullQuery, GL_QUERY_RESULT, &visibleInstances);
}

void Instancing::render(AbstractMesh* mesh) {
    glBindVertexArray(mesh->getVAO());

	glBindBuffer(GL_ARRAY_BUFFER, positionsTFB);
    glVertexAttribPointer(ShaderLayout::INSTANCE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ShaderLayout::INSTANCE_POSITION);
	glVertexAttribDivisor(ShaderLayout::INSTANCE_POSITION, 1);

	if (bytesOfInstanceNormals > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, normalsTFB);
		glVertexAttribPointer(ShaderLayout::INSTANCE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(ShaderLayout::INSTANCE_NORMAL);
		glVertexAttribDivisor(ShaderLayout::INSTANCE_NORMAL, 1);
	}

	int indices = mesh->getNumberOfIndices();

	if (indices > 0) {
		glDrawElementsInstanced(GL_TRIANGLES, indices, GL_UNSIGNED_INT, (GLvoid*) 0, visibleInstances);
	} else {
		glDrawArraysInstanced(GL_TRIANGLES, 0, mesh->getNumberOfVertices(), visibleInstances);
	}
}
