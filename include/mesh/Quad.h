#pragma once

#include "AbstractMesh.h"

using namespace glm;


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

	virtual vec3 getPositiveExtent() const override { return points[3]; }
	virtual vec3 getNegativeExtent() const override { return points[3]; }

private:
	static vec3 points[4];

	virtual void prepareBufferData() override;
};
