#pragma once
#include <GL/glew.h>
#include "AbstractNode.h"
#include "MeshNode.h"
#include "../mesh/Quad.h"
#include "../Texture2D.h"
#include "../components/SimpleDraw.h"
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
	~Skybox();

	void buildSkybox();

protected:
	// Rendering
	#pragma warning(push)
	#pragma warning(disable:4100) // ignore unused parameters
	virtual void renderThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override {}
	virtual void renderIDThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override {}
	#pragma warning(pop)

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

	ShaderProgram shaderSkybox;

	vector<Texture2D*> textures;

	MeshNode* nLeft;
	MeshNode* nBack;
	MeshNode* nRight;
	MeshNode* nFront;
	MeshNode* nTop;
	MeshNode* nBottom;

};
