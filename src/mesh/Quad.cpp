#include "mesh/Quad.h"


vec3 Quad::points[4] = {
	vec3(-0.5f, -0.5f, 0.0f),
	vec3(-0.5f, 0.5f, 0.0f),
	vec3(0.5f, -0.5f, 0.0f),
	vec3(0.5f, 0.5f, 0.0f)
};

Quad::Quad() : AbstractMesh() {
	useIBO = true;
	prepareBufferData();
	buildVAO();

	positiveExtent = points[3];
	negativeExtent = points[0];
}

void Quad::prepareBufferData() {
	numberOfVertices = 4;

	vertices = new vec4[numberOfVertices];
	normals = new vec3[numberOfVertices];
	texCoords = new vec2[numberOfVertices];

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	bytesOfVertices = sizeof(vec4) * numberOfVertices;
	bytesOfNormals = sizeof(vec3) * numberOfVertices;
	bytesOfTexCoords = sizeof(vec2) * numberOfVertices;

	vec3 normal(0.0f, 0.0f, -1.0f);

	for (unsigned int i = 0; i < numberOfVertices; ++i) {
		vertices[i] = vec4(points[i], 1.0f);
		normals[i] = normal;
	}

	texCoords[0] = vec2(1.0f, 1.0f);
	texCoords[1] = vec2(1.0f, 0.0f);
	texCoords[2] = vec2(0.0f, 1.0f);
	texCoords[3] = vec2(0.0f, 0.0f);
}
