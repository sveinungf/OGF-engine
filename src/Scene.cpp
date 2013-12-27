#include "Scene.h"


Scene::Scene() {
	camera = new Camera(75.0f, 0.01f, 435.0f);
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
	camera->setPosition(vec3(cameraPosition));
}

void Scene::render() {
	camera->render();
	rootNode->render(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}

void Scene::renderID() {
	camera->renderID();
	rootNode->renderID(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}

void Scene::addSkybox(){
	skybox = new Skybox();
	skybox->buildSkybox();
	camera->add(skybox);
}
