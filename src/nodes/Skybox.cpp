#include "nodes/Skybox.h"


enum { SKY_LEFT = 0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM };

Skybox::Skybox() : AbstractNode() {
	init();
}

Skybox::~Skybox(){
	for (Texture2D* texture : textures) {
		delete texture;
	}
}

void Skybox::init(){
	std::string resourceBase(OGF_RESOURCE_DIR);

	size = 500.0f;  //Max zFar distance for camera atm
	

	positionLeft = glm::vec3(0.5f, 0.0f, 0.0f) * glm::vec3(size, size, size);
	positionFront = glm::vec3(0.0f, 0.0f, 0.5f) * glm::vec3(size, size, size);
	positionRight = glm::vec3(-0.5f, 0.0f, 0.0f) * glm::vec3(size, size, size);
	positionBack = glm::vec3(0.0f, 0.0f, -0.5f) * glm::vec3(size, size, size);
	positionTop = glm::vec3(0.0f, 0.5f, 0.0f) * glm::vec3(size, size, size);
	positionBottom = glm::vec3(0.0f, -0.5f, 0.0f) * glm::vec3(size, size, size);

	ShaderProgram skyboxShader;
	skyboxShader << Shader(resourceBase + "/shaders/vSkybox.glsl", Shader::VERT)
			<< Shader(resourceBase + "/shaders/fSkybox.glsl", Shader::FRAG)
			<< Shader::LINK;

	//initialize front
	nFront = new MeshNode(skyboxShader, new Quad());
	children.push_back(nFront);

	//initialize left
	nLeft = new MeshNode(skyboxShader, new Quad());
	children.push_back(nLeft);

	//initialize right
	nRight = new MeshNode(skyboxShader, new Quad());
	children.push_back(nRight);

	//initialize back
	nBack = new MeshNode(skyboxShader, new Quad());
	children.push_back(nBack);

	//initialize top
	nTop = new MeshNode(skyboxShader, new Quad());
	children.push_back(nTop);

	//initialize bottom
	nBottom = new MeshNode(skyboxShader, new Quad());
	children.push_back(nBottom);

	loadTextures();
}

void Skybox::loadTextures(){
	std::string resourceBase(OGF_RESOURCE_DIR);

	textures.push_back(new Texture2D(resourceBase + "/skyboxes/left.bmp"));
	textures.push_back(new Texture2D(resourceBase + "/skyboxes/back.bmp"));
	textures.push_back(new Texture2D(resourceBase + "/skyboxes/right.bmp"));
	textures.push_back(new Texture2D(resourceBase + "/skyboxes/front.bmp"));
	textures.push_back(new Texture2D(resourceBase + "/skyboxes/top.bmp"));
	textures.push_back(new Texture2D(resourceBase + "/skyboxes/bottom.bmp"));
}

void Skybox::buildSkybox(){
	SimpleDraw* simpleDraw = new SimpleDraw();

	//front
	nFront->move(positionFront);
	nFront->scale(size, size, size);
	nFront->addComponent(simpleDraw);
	nFront->addTexture(textures[SKY_FRONT]);

	//left
	nLeft->rotateAroundSelfY(90.0f);
	nLeft->move(positionLeft);
	nLeft->scale(size, size, size);
	nLeft->addComponent(simpleDraw);
	nLeft->addTexture(textures[SKY_LEFT]);

	//right
	nRight->rotateAroundSelfY(-90.0f);
	nRight->move(positionRight);
	nRight->scale(size, size, size);
	nRight->addComponent(simpleDraw);
	nRight->addTexture(textures[SKY_RIGHT]);

	//back
	nBack->rotateAroundSelfY(180.0f);
	nBack->move(positionBack);
	nBack->scale(size, size, size);
	nBack->addComponent(simpleDraw);
	nBack->addTexture(textures[SKY_BACK]);

	//top
	nTop->rotateAroundSelfX(-90.0f);
	nTop->move(positionTop);
	nTop->scale(size, size, size);
	nTop->addComponent(simpleDraw);
	nTop->addTexture(textures[SKY_TOP]);

	//bottom
	nBottom->rotateAroundSelfX(90.0f);
	nBottom->move(positionBottom);
	nBottom->scale(size, size, size);
	nBottom->addComponent(simpleDraw);
	nBottom->addTexture(textures[SKY_BOTTOM]);
}
