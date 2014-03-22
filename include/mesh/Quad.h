#pragma once

#include "AbstractMesh.h"


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

private:
	static glm::vec3 points[4];

	virtual void prepareBufferData() override;
};
