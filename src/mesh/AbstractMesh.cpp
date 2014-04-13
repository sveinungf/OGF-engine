#include "mesh/AbstractMesh.h"

using namespace glm;


unsigned int AbstractMesh::count = 0;

glm::vec2 AbstractMesh::texture2DCorners[MAX_CORNERS_2D] = {
	glm::vec2(0.0f, 0.0f),	// LEFT_BOTTOM
	glm::vec2(0.0f, 1.0f),	// LEFT_TOP
	glm::vec2(1.0f, 0.0f),	// RIGHT_BOTTOM
	glm::vec2(1.0f, 1.0f)	// RIGHT_TOP
};

AbstractMesh::AbstractMesh() : id(++count), vao(0), vbo(0), ibo(0) {}

void AbstractMesh::buildVAO() {
    glGenVertexArrays(1, &vao); // Create our Vertex Array Object
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it
    glGenBuffers(1, &vbo); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind our Vertex Buffer Object
	
	int bytesOfVertices = sizeof(vec4) * vertices.size();
	int bytesOfNormals = sizeof(vec3) * normals.size();
	int bytesOfTexCoords = sizeof(vec2) * texCoords.size();
	int bytesOfColors = sizeof(vec4) * colors.size();
	int bytesOfTangents = sizeof(vec3) * tangents.size();
	int bytesOfBitangents = sizeof(vec3) * bitangents.size();
	int bytesOfIndices = sizeof(GLuint) * indices.size();

    glBufferData(GL_ARRAY_BUFFER, bytesOfVertices + bytesOfNormals + bytesOfColors + bytesOfTexCoords + bytesOfTangents + bytesOfBitangents, 0, GL_STATIC_DRAW);
				
	GLintptr offset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfVertices, &vertices[0]);
	glEnableVertexAttribArray(ShaderLayout::POSITION);
	glVertexAttribPointer(ShaderLayout::POSITION, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
    offset += bytesOfVertices;

	if (bytesOfNormals > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfNormals, &normals[0]);
		glEnableVertexAttribArray(ShaderLayout::NORMAL);
		glVertexAttribPointer(ShaderLayout::NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
		offset += bytesOfNormals;
	}

	if (bytesOfTexCoords > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfTexCoords, &texCoords[0]);
		glEnableVertexAttribArray(ShaderLayout::TEXCOORD);
		glVertexAttribPointer(ShaderLayout::TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
		offset += bytesOfTexCoords;
	}

	if (bytesOfColors > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfColors, &colors[0]);
		glEnableVertexAttribArray(ShaderLayout::COLOR);
		glVertexAttribPointer(ShaderLayout::COLOR, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
		offset += bytesOfColors;
	}

	if (bytesOfTangents > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfTangents, &tangents[0]);
		glEnableVertexAttribArray(ShaderLayout::TANGENT);
		glVertexAttribPointer(ShaderLayout::TANGENT, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
		offset += bytesOfTangents;
	}

	if (bytesOfBitangents > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, bytesOfBitangents, &bitangents[0]);
		glEnableVertexAttribArray(ShaderLayout::BITANGENT);
		glVertexAttribPointer(ShaderLayout::BITANGENT, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
		offset += bytesOfBitangents;
	}

	if (bytesOfIndices > 0) {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesOfIndices, &indices[0], GL_STATIC_DRAW);
	}
}
