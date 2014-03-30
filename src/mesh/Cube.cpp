#include "mesh/Cube.h"


glm::vec3 Cube::originalCube[Cube::MAX_CORNERS_3D] = {
	glm::vec3(-0.5f, -0.5f, -0.5f),		// LEFT_BOTTOM_FRONT
	glm::vec3(-0.5f, -0.5f, 0.5f),		// LEFT_BOTTOM_BACK
	glm::vec3(-0.5f, 0.5f, -0.5f),		// LEFT_TOP_FRONT
    glm::vec3(-0.5f, 0.5f, 0.5f),		// LEFT_TOP_BACK
	glm::vec3(0.5f, -0.5f, -0.5f),		// RIGHT_BOTTOM_FRONT
	glm::vec3(0.5f, -0.5f, 0.5f),		// RIGHT_BOTTOM_BACK
	glm::vec3(0.5f, 0.5f, -0.5f),		// RIGHT_TOP_FRONT
    glm::vec3(0.5f, 0.5f, 0.5f)			// RIGHT_TOP_BACK
};

Cube::Cube(const bool invert) : AbstractMesh(), inverted(invert) {
	useIBO = true;
	prepareBufferData();
	buildVAO();
}

Cube::Cube(const glm::vec4& color, const bool invert) : AbstractMesh(), inverted(invert) {
	useIBO = true;
	prepareBufferData(color);
	buildVAO();
}

void Cube::prepareBufferData() {
	prepareBufferData(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
}

void Cube::prepareBufferData(const glm::vec4& color) {
	numberOfVertices = 24; // 4 vertices per face * 6 faces
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
		// Left
		buildSide(index, LEFT_TOP_FRONT, LEFT_BOTTOM_FRONT, LEFT_BOTTOM_BACK, LEFT_TOP_BACK);
		// Right
		buildSide(index, RIGHT_TOP_BACK, RIGHT_BOTTOM_BACK, RIGHT_BOTTOM_FRONT, RIGHT_TOP_FRONT);
		// Bottom
		buildSide(index, RIGHT_BOTTOM_BACK, LEFT_BOTTOM_BACK, LEFT_BOTTOM_FRONT, RIGHT_BOTTOM_FRONT);
		// Top
		buildSide(index, RIGHT_TOP_FRONT, LEFT_TOP_FRONT, LEFT_TOP_BACK, RIGHT_TOP_BACK);
		// Front
		buildSide(index, LEFT_BOTTOM_FRONT, LEFT_TOP_FRONT, RIGHT_TOP_FRONT, RIGHT_BOTTOM_FRONT);
		// Back
		buildSide(index, LEFT_TOP_BACK, LEFT_BOTTOM_BACK, RIGHT_BOTTOM_BACK, RIGHT_TOP_BACK);
	} else {
		// Left
		buildSide(index, LEFT_TOP_FRONT, LEFT_TOP_BACK, LEFT_BOTTOM_BACK, LEFT_BOTTOM_FRONT);
		// Right
		buildSide(index, RIGHT_TOP_BACK, RIGHT_TOP_FRONT, RIGHT_BOTTOM_FRONT, RIGHT_BOTTOM_BACK);
		// Bottom
		buildSide(index, RIGHT_BOTTOM_BACK, RIGHT_BOTTOM_FRONT, LEFT_BOTTOM_FRONT, LEFT_BOTTOM_BACK);
		// Top
		buildSide(index, RIGHT_TOP_FRONT, RIGHT_TOP_BACK, LEFT_TOP_BACK, LEFT_TOP_FRONT);
		// Front
		buildSide(index, LEFT_BOTTOM_FRONT, RIGHT_BOTTOM_FRONT, RIGHT_TOP_FRONT, LEFT_TOP_FRONT);
		// Back
		buildSide(index, LEFT_TOP_BACK, RIGHT_TOP_BACK, RIGHT_BOTTOM_BACK, LEFT_BOTTOM_BACK);
	}
}

void Cube::buildSide(int& index, const Corner3D a, const Corner3D b, const Corner3D c, const Corner3D d) {
	normals[index] = originalCube[a];
	vertices[index] = glm::vec4(originalCube[a], 1.0f);
	texCoords[index] = texture2DCorners[LEFT_BOTTOM];
	++index;
	
	normals[index] = originalCube[b];
	vertices[index] = glm::vec4(originalCube[b], 1.0f);
	texCoords[index] = texture2DCorners[LEFT_TOP];
	++index;
	
	normals[index] = originalCube[c];
	vertices[index] = glm::vec4(originalCube[c], 1.0f);
	texCoords[index] = texture2DCorners[RIGHT_TOP];
	++index;

    normals[index] = originalCube[d];
    vertices[index] = glm::vec4(originalCube[d], 1.0f);
	texCoords[index] = texture2DCorners[RIGHT_BOTTOM];
	++index;

	indices.push_back(index - 3);
	indices.push_back(index - 2);
	indices.push_back(index - 4);

	indices.push_back(index - 2);
	indices.push_back(index - 1);
	indices.push_back(index - 4);
}
