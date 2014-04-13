#pragma once

#include "AbstractMesh.h"


class Cube : public AbstractMesh {

public:
	explicit Cube(const bool invert = false);
	virtual ~Cube() override {}

	// Virtual constructor idiom
	virtual Cube* clone() const override { return new Cube(*this); }

private:
	enum Corner3D {
		LEFT_BOTTOM_FRONT = 0,
		LEFT_BOTTOM_BACK,
		LEFT_TOP_FRONT,
		LEFT_TOP_BACK,
		RIGHT_BOTTOM_FRONT,
		RIGHT_BOTTOM_BACK,
		RIGHT_TOP_FRONT,
		RIGHT_TOP_BACK,
		//----------------
		MAX_CORNERS_3D
	};

	static glm::vec3 originalCube[MAX_CORNERS_3D];

	bool inverted;

	void buildSide(int& index, const Corner3D a, const Corner3D b, const Corner3D c, const Corner3D d);
	void prepareBufferData();
};
