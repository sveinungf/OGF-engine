#pragma once

#include "AbstractMesh.h"

using namespace glm;


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

private:
	static vec3 points[4];

	virtual void prepareBufferData() override;
};
