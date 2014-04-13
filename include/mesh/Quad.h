#pragma once

#include "AbstractMesh.h"


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

	// Virtual constructor idiom
	virtual Quad* clone() const override { return new Quad(*this); }

private:
	static glm::vec3 points[MAX_CORNERS_2D];

	void prepareBufferData();
};
