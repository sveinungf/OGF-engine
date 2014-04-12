#include "Scene.h"

using namespace glm;


Scene::Scene(const Skybox& theSkybox, ShaderManager* sManager) : rootNode(nullptr), camera(75.0f, 0.01f, 435.0f), shaderManager(sManager), skybox(theSkybox) {
}

void Scene::setCameraPosition(const vec3& cameraPosition) {
	camera.setPosition(cameraPosition);
}

void Scene::render() {
	shaderManager->updateLightPositions();
	camera.render();
	skybox.render(camera.getWorldToViewNoTranslation(), camera.getViewToClip(), nullptr);
	rootNode->render(camera.getWorldToView(), camera.getViewToClip(), nullptr);
}

void Scene::renderID() {
	shaderManager->updateLightPositions();
	camera.renderID();
	skybox.renderID(camera.getWorldToViewNoTranslation(), camera.getViewToClip(), nullptr);
	rootNode->renderID(camera.getWorldToView(), camera.getViewToClip(), nullptr);
}
