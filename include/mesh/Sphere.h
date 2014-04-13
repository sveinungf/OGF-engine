#pragma once

#include "AbstractMesh.h"

#define _USE_MATH_DEFINES


class Sphere : public AbstractMesh {

public:
	Sphere();
	virtual ~Sphere() override {}

	// Virtual constructor idiom
	virtual Sphere* clone() const override { return new Sphere(*this); }

private:
	void prepareBufferData();

	// Sphere generating stuff
	GLfloat divideByZeroTolerance;

	void triangle(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c);
	glm::vec4 unit(const glm::vec4& p) const;
	void divideTriangle(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c, const int count);
	void tetrahedron(const int count);

};
