#pragma once

#include "AbstractMesh.h"


class Quad : public AbstractMesh {

public:
	Quad();
	virtual ~Quad() override {}

private:
	static enum Corner {
		LEFT_TOP = 0,
		RIGHT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
		//----------------
		MAX_CORNERS
	};

	static glm::vec3 points[MAX_CORNERS];

	virtual void prepareBufferData() override;
};
