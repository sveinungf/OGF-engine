#include "Scene.h"


Scene::Scene() {
	camera = new Camera();
	
}

Scene::~Scene() {
    delete rootNode;
	delete camera;
}

void Scene::setRootNode(AbstractNode* node) {
	rootNode = node;
}

Camera* Scene::getCamera(){
	return camera;
}

void Scene::setCamera(Camera* camera){
	this->camera = camera;
}

void Scene::setCameraPosition(glm::vec4 cameraPosition){
	this->camera->setPosition(cameraPosition);
}


void Scene::render() {
	rootNode->render(camera->getWorldToView(), camera->getViewToClip());

	if (skybox != nullptr){
		skybox->setPosition(glm::vec3(camera->getPosition()));
		skybox->render(camera->getWorldToView(), camera->getViewToClip(), nullptr);
	}
}

void Scene::addSkybox(){
	skybox = new Skybox();
	skybox->buildSkybox();
}
