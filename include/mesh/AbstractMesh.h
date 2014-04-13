#pragma once

#include <vector>
#include <GL/glew.h>
#include <glmhppnowarnings.h>
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

	
	int getNumberOfVertices() const { return vertices.size(); }
	int getNumberOfIndices() const { return indices.size(); }
	unsigned int getId() const { return id; }
	const GLuint getVAO() const { return vao; }

	// The xyz-values of the vertices furthest from the mesh's origo. Used to create a bounding box around the mesh.
	// negativeExtent usually contains negative values.
	const glm::vec3& getPositiveExtent() const { return positiveExtent; }
	const glm::vec3& getNegativeExtent() const { return negativeExtent; }

protected:
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<GLuint> indices;

	unsigned int id;
	
	glm::vec3 positiveExtent;
	glm::vec3 negativeExtent;

	// Constructor
	AbstractMesh();

	void buildVAO();

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};
