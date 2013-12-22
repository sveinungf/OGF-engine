#include "mesh/Quad.h"


vec3 Quad::points[4] = {
	vec3(-0.5f, -0.5f, 0.0f),
	vec3(-0.5f, 0.5f, 0.0f),
	vec3(0.5f, -0.5f, 0.0f),
	vec3(0.5f, 0.5f, 0.0f)
};

Quad::Quad() : AbstractMesh() {
	prepareBufferData();
	buildVAO();
}

void Quad::prepareBufferData() {
	numberOfVertices = 6;

	vertices = new vec4[numberOfVertices];
	normals = new vec3[numberOfVertices];
	texCoords = new vec2[numberOfVertices];

	bytesOfVertices = sizeof vec4 * numberOfVertices;
	bytesOfNormals = sizeof vec3 * numberOfVertices;
	bytesOfColors = 0;
	bytesOfTexCoords = sizeof vec2 * numberOfVertices;

	buildQuad(0, 1, 2, 3);
}

void Quad::buildQuad(int a, int b, int c, int d) {
	int index = 0;
	vec3 normal(0.0f, 0.0f, -1.0f);

	vertices[index] = vec4(points[a], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(1.0, 1.0);
	index++;

	vertices[index] = vec4(points[b], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(1.0, 0.0);
	index++;

	vertices[index] = vec4(points[c], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(0.0, 1.0);
	index++;

	vertices[index] = vec4(points[b], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(1.0, 0.0);
	index++;

	vertices[index] = vec4(points[d], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(0.0, 0.0);
	index++;

	vertices[index] = vec4(points[c], 1.0f);
	normals[index] = normal;
	texCoords[index] = vec2(0.0, 1.0);
	index++;
}
