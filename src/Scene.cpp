#include "Scene.h"

using namespace glm;


Scene::Scene() : rootNode(nullptr), skybox(nullptr) {
	camera = new Camera(75.0f, 0.01f, 435.0f);
}

Scene::~Scene() {
    delete rootNode;
	delete skybox;
	delete camera;
}

void Scene::init() {
	skybox = new Skybox();
}

void Scene::setCameraPosition(const vec3& cameraPosition){
	camera->setPosition(cameraPosition);
}

void Scene::render() {
	camera->render();
	skybox->render(camera->getWorldToViewNoTranslation(), camera->getViewToClip(), nullptr);
	rootNode->render(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}

void Scene::renderID() {
	camera->renderID();
	skybox->renderID(camera->getWorldToViewNoTranslation(), camera->getViewToClip(), nullptr);
	rootNode->renderID(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}
