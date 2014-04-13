#include "mesh/Quad.h"

using namespace glm;
using namespace std;


vec3 Quad::points[MAX_CORNERS_2D] = {
	vec3(-0.5f, -0.5f, 0.0f),	// LEFT_BOTTOM
	vec3(-0.5f, 0.5f, 0.0f),	// LEFT_TOP
	vec3(0.5f, -0.5f, 0.0f),	// RIGHT_BOTTOM
	vec3(0.5f, 0.5f, 0.0f)		// RIGHT_TOP
};

Quad::Quad() : AbstractMesh() {
	prepareBufferData();
	buildVAO();

	positiveExtent = points[RIGHT_TOP];
	negativeExtent = points[LEFT_BOTTOM];
}

void Quad::prepareBufferData() {
	int numberOfVertices = MAX_CORNERS_2D;
	vec3 normal(0.0f, 0.0f, 1.0f);

	vertices.reserve(numberOfVertices);
	normals = vector<vec3>(numberOfVertices, normal); // Fills the vector with the default value 'normal'
	texCoords.reserve(numberOfVertices);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	for (int i = 0; i < numberOfVertices; ++i) {
		vertices.push_back(vec4(points[i], 1.0f));
		texCoords.push_back(texture2DCorners[i]);
	}
}
