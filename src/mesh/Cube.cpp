#include "mesh/Cube.h"


glm::vec3 Cube::originalCube[Cube::MAX_CORNERS] = {
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, 0.5f,  0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f)
};

Cube::Cube(const bool invert) : AbstractMesh(), inverted(invert) {
	prepareBufferData();
	buildVAO();
}

Cube::Cube(const glm::vec4& color, const bool invert) : AbstractMesh(), inverted(invert) {
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

	if (!inverted) {
		// Back
		buildSide(index, TOP_LEFT_BACK, BOTTOM_LEFT_BACK, BOTTOM_RIGHT_BACK, TOP_RIGHT_BACK);
		// Right
		buildSide(index, TOP_RIGHT_BACK, BOTTOM_RIGHT_BACK, BOTTOM_RIGHT_FRONT, TOP_RIGHT_FRONT);
		// Bottom
		buildSide(index, BOTTOM_RIGHT_BACK, BOTTOM_LEFT_BACK, BOTTOM_LEFT_FRONT, BOTTOM_RIGHT_FRONT);
		// Top
		buildSide(index, TOP_RIGHT_FRONT, TOP_LEFT_FRONT, TOP_LEFT_BACK, TOP_RIGHT_BACK);
		// Front
		buildSide(index, BOTTOM_LEFT_FRONT, TOP_LEFT_FRONT, TOP_RIGHT_FRONT, BOTTOM_RIGHT_FRONT);
		// Left
		buildSide(index, TOP_LEFT_FRONT, BOTTOM_LEFT_FRONT, BOTTOM_LEFT_BACK, TOP_LEFT_BACK);
	} else {
		// Back
		buildSide(index, TOP_LEFT_BACK, TOP_RIGHT_BACK, BOTTOM_RIGHT_BACK, BOTTOM_LEFT_BACK);
		// Right
		buildSide(index, TOP_RIGHT_BACK, TOP_RIGHT_FRONT, BOTTOM_RIGHT_FRONT, BOTTOM_RIGHT_BACK);
		// Bottom
		buildSide(index, BOTTOM_RIGHT_BACK, BOTTOM_RIGHT_FRONT, BOTTOM_LEFT_FRONT, BOTTOM_LEFT_BACK);
		// Top
		buildSide(index, TOP_RIGHT_FRONT, TOP_RIGHT_BACK, TOP_LEFT_BACK, TOP_LEFT_FRONT);
		// Front
		buildSide(index, BOTTOM_LEFT_FRONT, BOTTOM_RIGHT_FRONT, TOP_RIGHT_FRONT, TOP_LEFT_FRONT);
		// Left
		buildSide(index, TOP_LEFT_FRONT, TOP_LEFT_BACK, BOTTOM_LEFT_BACK, BOTTOM_LEFT_FRONT);
	}
}

void Cube::buildSide(int& index, const Corner a, const Corner b, const Corner c, const Corner d) {
    normals[index] = originalCube[a];
    vertices[index] = glm::vec4(originalCube[a], 1.0f);
    texCoords[index] = glm::vec2(0.0, 0.0);
	++index;

    normals[index] = originalCube[b];
    vertices[index] = glm::vec4(originalCube[b], 1.0f);
    texCoords[index] = glm::vec2(0.0, 1.0);
	++index;

    normals[index] = originalCube[c];
    vertices[index] = glm::vec4(originalCube[c], 1.0f);
    texCoords[index] = glm::vec2(1.0, 1.0);
	++index;

    normals[index] = originalCube[a];
    vertices[index] = glm::vec4(originalCube[a], 1.0f);
    texCoords[index] = glm::vec2(0.0, 0.0);
	++index;

    normals[index] = originalCube[c];
    vertices[index] = glm::vec4(originalCube[c], 1.0f);
    texCoords[index] = glm::vec2(1.0, 1.0);
	++index;

    normals[index] = originalCube[d];
    vertices[index] = glm::vec4(originalCube[d], 1.0f);
    texCoords[index] = glm::vec2(1.0, 0.0);
	++index;
}
