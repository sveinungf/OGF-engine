#pragma once

#include "AbstractMesh.h"

#define _USE_MATH_DEFINES

class Sphere : public AbstractMesh {

public:
	Sphere();
	virtual ~Sphere() override {}

private:
	virtual void prepareBufferData();

	// Sphere generating stuff
	GLfloat divideByZeroTolerance;
	GLuint index;

	void triangle( const glm::vec4& a, const glm::vec4& b, const glm::vec4& c );
	glm::vec4 unit( const glm::vec4& p );
	void divideTriangle( const glm::vec4& a, const glm::vec4& b, const glm::vec4& c, int count );
	void tetrahedron( int count );

};
