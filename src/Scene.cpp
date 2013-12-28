#include "Scene.h"


Scene::Scene() : rootNode(nullptr), skybox(nullptr) {
	camera = new Camera(75.0f, 0.01f, 435.0f);
}

Scene::~Scene() {
    delete rootNode;
	delete camera;
}

void Scene::init() {
	skybox = new Skybox();
	skybox->buildSkybox();

	camera->add(skybox);
}

void Scene::setCameraPosition(const vec3& cameraPosition){
	camera->setPosition(cameraPosition);
}

void Scene::render() {
	camera->render();
	rootNode->render(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}

void Scene::renderID() {
	camera->renderID();
	rootNode->renderID(camera->getWorldToView(), camera->getViewToClip(), nullptr);
}
