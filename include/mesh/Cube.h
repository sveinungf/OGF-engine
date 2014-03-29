#pragma once

#include "AbstractMesh.h"


class Cube : public AbstractMesh {

public:
	explicit Cube(const bool invert = false);
	explicit Cube(const glm::vec4& color, const bool invert = false);
	virtual ~Cube() override {}

protected:
	virtual void prepareBufferData() override;
	void prepareBufferData(const glm::vec4& color);

private:
	static enum Corner {
		BOTTOM_LEFT_BACK = 0,
		TOP_LEFT_BACK,
		TOP_RIGHT_BACK,
		BOTTOM_RIGHT_BACK,
		BOTTOM_LEFT_FRONT,
		TOP_LEFT_FRONT,
		TOP_RIGHT_FRONT,
		BOTTOM_RIGHT_FRONT,
		//----------------
		MAX_CORNERS
	};

	static glm::vec3 originalCube[MAX_CORNERS];

	bool inverted;

	void buildSide(int& index, const Corner a, const Corner b, const Corner c, const Corner d);
};
