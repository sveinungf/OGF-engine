#pragma once

#include "AbstractMesh.h"
#include <assimp/scene.h>


class AssImpMesh : public AbstractMesh {

public:
	AssImpMesh(aiMesh* mesh);
	virtual ~AssImpMesh() override {}

	virtual glm::vec3 getPositiveExtent() const override { return positiveExtent; }
	virtual glm::vec3 getNegativeExtent() const override { return negativeExtent; }

private:
	glm::vec3 positiveExtent;
	glm::vec3 negativeExtent;

	void prepareBufferData() override {}
	void computeTangentAndBitangetValues();
};
