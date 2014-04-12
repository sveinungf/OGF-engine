#pragma once

#include <vector>
#include <GL/glew.h>
#include <glmhppnowarnings.h>
#include <glm/ext.hpp>
#include "../ShaderLayout.h"


class AbstractMesh {

public:
	enum Corner2D {
		LEFT_BOTTOM = 0,
		LEFT_TOP,
		RIGHT_BOTTOM,
		RIGHT_TOP,
		//----------
		MAX_CORNERS_2D
	};

	static glm::vec2 texture2DCorners[MAX_CORNERS_2D];
	static unsigned int count;

	virtual ~AbstractMesh() {}

	// Virtual constructor idiom
	virtual AbstractMesh* clone() const = 0;

	const GLuint getVAO() const { return vao; }
	const GLuint getVBO() const { return vbo; }
	const GLintptr getBufferOffset() const { return bufferOffset; }
	void setBufferOffset(const GLintptr offset) { bufferOffset = offset; }
	const GLintptr getAttribOffset() const { return attribOffset; }
	void setAttribOffset(const GLintptr offset) { attribOffset = offset; }
	int getNumberOfVertices() const { return numberOfVertices; }
	int getNumberOfIndices() const { return indices.size(); }

	unsigned int getId() const { return id; }

	// The xyz-values of the vertices furthest from the mesh's origo. Used to create a bounding box around the mesh.
	// negativeExtent usually contains negative values.
	const glm::vec3& getPositiveExtent() const { return positiveExtent; }
	const glm::vec3& getNegativeExtent() const { return negativeExtent; }

protected:
	glm::vec4* vertices;
    glm::vec4* colors;
    glm::vec3* normals;
    glm::vec2* texCoords;
	glm::vec3* tangents;
	glm::vec3* bitangents;

	std::vector<GLuint> indices;

	unsigned int id;

	// All of these integers must be initiated in order to make things work
	unsigned int numberOfVertices;
	int bytesOfVertices;
	int bytesOfNormals;
	int bytesOfColors;
	int bytesOfTexCoords;
	int bytesOfTangents;
	int bytesOfBitangents;

	bool useIBO;
	
	glm::vec3 positiveExtent;
	glm::vec3 negativeExtent;

	AbstractMesh();

	virtual void prepareBufferData() = 0;
	void buildVAO();

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	GLintptr bufferOffset;
	GLintptr attribOffset;
};
