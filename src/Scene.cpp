#include "Scene.h"

using namespace glm;


Scene::Scene(const Skybox& theSkybox, ShaderManager* sManager, const int width, const int height) : rootNode(nullptr), camera(75.0f, 0.01f, 435.0f), shaderManager(sManager), skybox(theSkybox), waterSurfaceFBO(width, height) {
}

void Scene::setCameraPosition(const vec3& cameraPosition) {
	camera.setPosition(cameraPosition);
}

void Scene::setWaterNode(const std::shared_ptr<MeshNode>& node) {
	waterNode = node;
	waterNode->addTexture(waterSurfaceFBO.getTexture());
}

void Scene::updateWindowDimensions(const int width, const int height) {
	camera.updateWindowDimensions(width, height);
	waterSurfaceFBO.reshape(width, height);
}

void Scene::render() {
	shaderManager->updateLightPositions();
	camera.render();

	skybox.render(camera.getWorldToViewNoTranslation(), camera.getViewToClip());

	waterSurfaceFBO.enable();

	glEnable(GL_STENCIL_TEST);

	waterNode->render(camera.getWorldToView(), camera.getViewToClip());

	glCullFace(GL_FRONT);

	skybox.scale(1.0f, -1.0f, 1.0f);
	skybox.render(camera.getWorldToViewNoTranslation(), camera.getViewToClip());
	skybox.scale(1.0f, -1.0f, 1.0f);

	shaderManager->updateLightPositions(true);

	rootNode->getShaderProgram().setUniformGLint("discardUnderWater", 1);
	rootNode->scale(1.0f, -1.0f, 1.0f);
	rootNode->render(camera.getWorldToView(), camera.getViewToClip());
	rootNode->scale(1.0f, -1.0f, 1.0f);
	rootNode->getShaderProgram().setUniformGLint("discardUnderWater", 0);

	shaderManager->updateLightPositions(true);

	glCullFace(GL_BACK);
	glDisable(GL_STENCIL_TEST);

	waterSurfaceFBO.disable();

	rootNode->render(camera.getWorldToView(), camera.getViewToClip());

	waterNode->render(camera.getWorldToView(), camera.getViewToClip());
}

void Scene::renderID() {
	camera.renderID();
	skybox.renderID(camera.getWorldToViewNoTranslation(), camera.getViewToClip());
	rootNode->renderID(camera.getWorldToView(), camera.getViewToClip());
	waterNode->renderID(camera.getWorldToView(), camera.getViewToClip());
}
