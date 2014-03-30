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
		LEFT_BOTTOM_FRONT = 0,
		LEFT_BOTTOM_BACK,
		LEFT_TOP_FRONT,
		LEFT_TOP_BACK,
		RIGHT_BOTTOM_FRONT,
		RIGHT_BOTTOM_BACK,
		RIGHT_TOP_FRONT,
		RIGHT_TOP_BACK,
		//----------------
		MAX_CORNERS
	};

	static glm::vec3 originalCube[MAX_CORNERS];

	bool inverted;

	void buildSide(int& index, const Corner a, const Corner b, const Corner c, const Corner d);
};
