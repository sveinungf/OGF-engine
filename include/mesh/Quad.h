#pragma once

#include "AbstractMesh.h"


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

private:
	static glm::vec3 points[MAX_CORNERS_2D];

	virtual void prepareBufferData() override;
};
