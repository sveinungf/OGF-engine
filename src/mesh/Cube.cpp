#include "mesh/Cube.h"


glm::vec3 Cube::originalCube[8] = {
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, 0.5f,  0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f)
};

Cube::Cube() : AbstractMesh() {
	prepareBufferData();
	buildVAO();
}

Cube::Cube(const glm::vec4& color) : AbstractMesh() {
	prepareBufferData(color);
	buildVAO();
}

void Cube::prepareBufferData() {
	prepareBufferData(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
}

void Cube::prepareBufferData(const glm::vec4& color) {
	numberOfVertices = 36; // 6 vertices per face * 6 faces
	bytesOfVertices = sizeof(glm::vec4) * numberOfVertices;
	bytesOfNormals = sizeof(glm::vec3) * numberOfVertices;
	bytesOfColors = sizeof(glm::vec4) * numberOfVertices;
	bytesOfTexCoords = sizeof(glm::vec2) * numberOfVertices;

	vertices = new glm::vec4[numberOfVertices];
	normals = new glm::vec3[numberOfVertices];
	colors = new glm::vec4[numberOfVertices];
	texCoords = new glm::vec2[numberOfVertices];

	for (unsigned int i = 0; i < numberOfVertices; ++i){
		colors[i] = color;
	}


	int index = 0;
	buildVertex(index, 1, 0, 3, 2); //Back
	index += 6;
	buildVertex(index, 2, 3, 7, 6); //Left
	index += 6;
	buildVertex(index, 3, 0, 4, 7); //Bottom
	index += 6;
	buildVertex(index, 6, 5, 1, 2); //Top
	index += 6;
	buildVertex(index, 4, 5, 6, 7); //Front
	index += 6;
	buildVertex(index, 5, 4, 0, 1); //Right

}


void Cube::buildVertex(int index, int a, int b, int c, int d) {
    normals[index] = originalCube[a];
    vertices[index] = glm::vec4(originalCube[a], 1.0f);
    texCoords[index] = glm::vec2(0.0, 0.0);
    index++;

    normals[index] = originalCube[b];
    vertices[index] = glm::vec4(originalCube[b], 1.0f);
    texCoords[index] = glm::vec2(0.0, 1.0);
    index++;

    normals[index] = originalCube[c];
    vertices[index] = glm::vec4(originalCube[c], 1.0f);
    texCoords[index] = glm::vec2(1.0, 1.0);
    index++;

    normals[index] = originalCube[a];
    vertices[index] = glm::vec4(originalCube[a], 1.0f);
    texCoords[index] = glm::vec2(0.0, 0.0);
    index++;

    normals[index] = originalCube[c];
    vertices[index] = glm::vec4(originalCube[c], 1.0f);
    texCoords[index] = glm::vec2(1.0, 1.0);
    index++;

    normals[index] = originalCube[d];
    vertices[index] = glm::vec4(originalCube[d], 1.0f);
    texCoords[index] = glm::vec2(1.0, 0.0);
    index++;

}
