#pragma once
#include <GL/glew.h>
#include "AbstractNode.h"
#include "MeshNode.h"
#include "../mesh/Quad.h"
#include "../Texture2D.h"
#include "../components/IBODraw.h"
#include <vector>
#include "OGFConfig.h"

/**
	THIS CLASS NEEDS TO BE AN ORPHAN
	DO NOT ADD THIS NODE TO ANY OTHER NODES!

	Prime use is in Scene that adds this as its skybox;
*/

class Skybox : public AbstractNode {

public:
	Skybox();
	virtual ~Skybox() override;

	void buildSkybox();

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}

private:
	
	void loadTextures();
	void init();
	
	glm::vec3 positionLeft;
	glm::vec3 positionBack;
	glm::vec3 positionRight;
	glm::vec3 positionFront;
	glm::vec3 positionTop;
	glm::vec3 positionBottom;

	float size;

	std::vector<Texture2D*> textures;

	MeshNode* nLeft;
	MeshNode* nBack;
	MeshNode* nRight;
	MeshNode* nFront;
	MeshNode* nTop;
	MeshNode* nBottom;
};
