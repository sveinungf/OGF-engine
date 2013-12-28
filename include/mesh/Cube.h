#pragma once

#include "AbstractMesh.h"


class Cube : public AbstractMesh {

public:
	Cube();
	Cube(glm::vec4 color);

protected:
	virtual void prepareBufferData() override;
	void prepareBufferData(glm::vec4 color);

private:
	//Stuff used to create the Cube. Not OpenGL related.
	static glm::vec3 originalCube[8];

	void buildVertex(int index, int a, int b, int c, int d);
};
