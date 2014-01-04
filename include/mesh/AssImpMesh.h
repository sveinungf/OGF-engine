#pragma once

#include "AbstractMesh.h"
#include <assimp/scene.h>


class AssImpMesh : public AbstractMesh {

public:
	AssImpMesh(aiMesh* mesh);
	virtual ~AssImpMesh() override {}

private:
	void prepareBufferData() override {}
	void computeTangentAndBitangetValues();
};
