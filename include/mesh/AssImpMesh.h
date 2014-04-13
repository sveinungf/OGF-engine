#pragma once

#include "AbstractMesh.h"
#include <assimp/scene.h>


class AssImpMesh : public AbstractMesh {

public:
	explicit AssImpMesh(aiMesh* mesh);
	virtual ~AssImpMesh() override {}

	// Virtual constructor idiom
	virtual AssImpMesh* clone() const override { return new AssImpMesh(*this); }

private:
	void computeTangentAndBitangetValues(const unsigned int numberOfVertices);
};
