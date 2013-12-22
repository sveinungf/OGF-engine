#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include <glm/ext.hpp>

#include "../Debug.h"
#include "../ShaderLayout.h"


class AbstractMesh {

public:
	AbstractMesh();
	virtual ~AbstractMesh() {}

	static unsigned int count;

	const GLuint& getVAO() const { return vao; }
	const GLuint& getVBO() const { return vbo; }
	const GLintptr& getBufferOffset() const { return bufferOffset; }
	void setBufferOffset(const GLintptr& offset) { bufferOffset = offset; }
	const GLintptr& getAttribOffset() const { return attribOffset; }
	void setAttribOffset(const GLintptr& offset) { attribOffset = offset; }
	int getNumberOfVertices() const { return numberOfVertices; }

	unsigned int getId(){ return id; }

	virtual glm::vec3 getPositiveExtent() const { return glm::vec3(0.0f, 0.0f, 0.0f); }
	virtual glm::vec3 getNegativeExtent() const { return glm::vec3(0.0f, 0.0f, 0.0f); }

protected:
	glm::vec4* vertices;
    glm::vec4* colors;
    glm::vec3* normals;
    glm::vec2* texCoords;
	glm::vec3* tangents;
	glm::vec3* bitangents;

	unsigned int id;

	// All of these integers must be initiated in order to make things work
	unsigned int numberOfVertices;
	int bytesOfVertices;
	int bytesOfNormals;
	int bytesOfColors;
	int bytesOfTexCoords;
	int bytesOfTangents;
	int bytesOfBitangents;

	virtual void prepareBufferData() = 0;
	void buildVAO();

private:
	GLuint vao;
	GLuint vbo;

	GLintptr bufferOffset;
	GLintptr attribOffset;
};
