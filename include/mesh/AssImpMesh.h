#include "AbstractMesh.h"
#include <assimp/scene.h>


class AssImpMesh : public AbstractMesh {

private:
	glm::vec3 positiveExtent;
	glm::vec3 negativeExtent;

	void prepareBufferData() override {}
	void computeTangentAndBitangetValues();

public:
	AssImpMesh(aiMesh* mesh);

	virtual glm::vec3 getPositiveExtent() const override { return positiveExtent; }
	virtual glm::vec3 getNegativeExtent() const override { return negativeExtent; }
};
