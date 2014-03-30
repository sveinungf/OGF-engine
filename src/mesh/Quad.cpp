#include "mesh/Quad.h"

using namespace glm;


vec3 Quad::points[4] = {
	vec3(-0.5f, -0.5f, 0.0f),	// LEFT_BOTTOM
	vec3(-0.5f, 0.5f, 0.0f),	// LEFT_TOP
	vec3(0.5f, -0.5f, 0.0f),	// RIGHT_BOTTOM
	vec3(0.5f, 0.5f, 0.0f)		// RIGHT_TOP
};

Quad::Quad() : AbstractMesh() {
	useIBO = true;
	prepareBufferData();
	buildVAO();

	positiveExtent = points[RIGHT_TOP];
	negativeExtent = points[LEFT_BOTTOM];
}

void Quad::prepareBufferData() {
	numberOfVertices = 4;

	vertices = new vec4[numberOfVertices];
	normals = new vec3[numberOfVertices];
	texCoords = new vec2[numberOfVertices];

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	bytesOfVertices = sizeof(vec4) * numberOfVertices;
	bytesOfNormals = sizeof(vec3) * numberOfVertices;
	bytesOfTexCoords = sizeof(vec2) * numberOfVertices;

	vec3 normal(0.0f, 0.0f, 1.0f);

	for (unsigned int i = 0; i < numberOfVertices; ++i) {
		vertices[i] = vec4(points[i], 1.0f);
		normals[i] = normal;
		texCoords[i] = texture2DCorners[i];
	}
}
