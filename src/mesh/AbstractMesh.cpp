#include "mesh/AbstractMesh.h"


glm::vec2 AbstractMesh::texture2DCorners[MAX_TEXTURE_CORNERS] = {
	glm::vec2(0.0f, 1.0f),	// UPPER_LEFT
	glm::vec2(1.0f, 1.0f),	// UPPER_RIGHT
	glm::vec2(0.0f, 0.0f),	// LOWER_LEFT
	glm::vec2(1.0f, 0.0f)	// LOWER_RIGHT
};

AbstractMesh::AbstractMesh() :
		vertices(nullptr), colors(nullptr), normals(nullptr), texCoords(nullptr), tangents(nullptr), bitangents(nullptr),
		numberOfVertices(0), bytesOfVertices(0), bytesOfNormals(0), bytesOfColors(0), bytesOfTexCoords(0), bytesOfTangents(0), bytesOfBitangents(0),
		useIBO(false), vao(0), vbo(0), ibo(0), bufferOffset(0), attribOffset(0) {

	id = ++count;
}

void AbstractMesh::buildVAO() {
	checkErrorAndStop("MeshAbstract::buildVAO() : pre method excecution", true);

    glGenVertexArrays(1, &vao); // Create our Vertex Array Object
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it
    glGenBuffers(1, &vbo); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind our Vertex Buffer Object

	if (useIBO) {
		int bytesOfIndices = sizeof(GLuint) * indices.size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesOfIndices, &indices[0], GL_STATIC_DRAW);
	}

	checkErrorAndStop("MeshAbstract::buildVAO() : Binding vao/vbo", true);
	
    glBufferData(GL_ARRAY_BUFFER,
		bytesOfVertices + bytesOfNormals + bytesOfColors + bytesOfTexCoords + bytesOfTangents + bytesOfBitangents, 0,
                 GL_STATIC_DRAW);
				 
    glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfVertices, vertices);
    bufferOffset += bytesOfVertices;
    glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfNormals, normals);
    bufferOffset += bytesOfNormals;
    glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfColors, colors);
    bufferOffset += bytesOfColors;
    glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfTexCoords, texCoords);
	bufferOffset += bytesOfTexCoords;
	glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfTangents, tangents);
	bufferOffset += bytesOfTangents;
	glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, bytesOfBitangents, bitangents);
	bufferOffset += bytesOfBitangents;

	checkErrorAndStop("MeshAbstract::buildVAO() : Sending data to the VBO", true);

    // Initiate our VBO with the apropriate state
    attribOffset = 0;
    glEnableVertexAttribArray(ShaderLayout::POSITION);
    glVertexAttribPointer(ShaderLayout::POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid*) attribOffset);
    attribOffset += bytesOfVertices;

    glEnableVertexAttribArray(ShaderLayout::NORMAL);
    glVertexAttribPointer(ShaderLayout::NORMAL, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid*) attribOffset);
    attribOffset += bytesOfNormals;

    glEnableVertexAttribArray(ShaderLayout::COLOR);
    glVertexAttribPointer(ShaderLayout::COLOR, 4, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid*) attribOffset);
    attribOffset += bytesOfColors;

	glEnableVertexAttribArray(ShaderLayout::TEXCOORD);
    glVertexAttribPointer(ShaderLayout::TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid*) attribOffset);
	attribOffset += bytesOfTexCoords;

	glEnableVertexAttribArray(ShaderLayout::TANGENT);
	glVertexAttribPointer(ShaderLayout::TANGENT, 3, GL_FLOAT, GL_FALSE, 0,
		(GLvoid*)attribOffset);
	attribOffset += bytesOfTangents;

	glEnableVertexAttribArray(ShaderLayout::BITANGENT);
	glVertexAttribPointer(ShaderLayout::BITANGENT, 3, GL_FLOAT, GL_FALSE, 0,
		(GLvoid*)attribOffset);
	attribOffset += bytesOfBitangents;

    checkErrorAndStop("MeshAbstract::buildVAO() : VertexAttribPointerArray", true);
}

unsigned int AbstractMesh::count = 0;
