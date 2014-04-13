#include "mesh/Cube.h"

using namespace glm;
using namespace std;


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
	prepareBufferData();
	buildVAO();
}

void Cube::prepareBufferData() {
	int numberOfVertices = 24; // 4 vertices per face * 6 faces
	vertices.reserve(numberOfVertices);
	normals.reserve(numberOfVertices);
	texCoords.reserve(numberOfVertices);

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
	normals.push_back(originalCube[a]);
	vertices.push_back(vec4(originalCube[a], 1.0f));
	texCoords.push_back(texture2DCorners[LEFT_BOTTOM]);
	
	normals.push_back(originalCube[b]);
	vertices.push_back(vec4(originalCube[b], 1.0f));
	texCoords.push_back(texture2DCorners[LEFT_TOP]);
	
	normals.push_back(originalCube[c]);
	vertices.push_back(vec4(originalCube[c], 1.0f));
	texCoords.push_back(texture2DCorners[RIGHT_TOP]);

	normals.push_back(originalCube[d]);
	vertices.push_back(vec4(originalCube[d], 1.0f));
	texCoords.push_back(texture2DCorners[RIGHT_BOTTOM]);

	indices.push_back(index + 1);
	indices.push_back(index + 2);
	indices.push_back(index);

	indices.push_back(index + 2);
	indices.push_back(index + 3);
	indices.push_back(index);

	index += 4;
}
