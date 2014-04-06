#pragma once

#include "AbstractMesh.h"
#include <assimp/scene.h>


class AssImpMesh : public AbstractMesh {

public:
	explicit AssImpMesh(aiMesh* mesh);

	// Virtual constructor idiom
	virtual AssImpMesh* clone() const override { return new AssImpMesh(*this); }

	virtual ~AssImpMesh() override {}

private:
	void prepareBufferData() override {}
	void computeTangentAndBitangetValues();
};
