#include "Scene.h"

using namespace glm;


Scene::Scene(const Skybox& theSkybox, ShaderManager* sManager, const int width, const int height) : rootNode(nullptr), camera(75.0f, 0.01f, 435.0f), shaderManager(sManager), skybox(theSkybox), waterSurfaceFBO(width, height) {
}

void Scene::setCameraPosition(const vec3& cameraPosition) {
	camera.setPosition(cameraPosition);
}

void Scene::updateWindowDimensions(const int width, const int height) {
	camera.updateWindowDimensions(width, height);
	waterSurfaceFBO.reshape(width, height);
}

void Scene::render() {
	shaderManager->updateLightPositions(true);
	camera.render();

	skybox.render(camera.getWorldToViewNoTranslation(), camera.getViewToClip());

	waterSurfaceFBO.enable();

	glEnable(GL_STENCIL_TEST);
	glCullFace(GL_FRONT);

	glEnable(GL_RASTERIZER_DISCARD);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	waterNode->render(camera.getWorldToView(), camera.getViewToClip());

	glStencilFunc(GL_EQUAL, 1, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_RASTERIZER_DISCARD);

	skybox.scale(1.0f, -1.0f, 1.0f);
	skybox.render(camera.getWorldToViewNoTranslation(), camera.getViewToClip());
	skybox.scale(1.0f, -1.0f, 1.0f);

	rootNode->getShaderProgram().setUniformGLint("discardUnderWater", 1);
	rootNode->scale(1.0f, -1.0f, 1.0f);
	rootNode->render(camera.getWorldToView(), camera.getViewToClip());
	rootNode->scale(1.0f, -1.0f, 1.0f);
	rootNode->getShaderProgram().setUniformGLint("discardUnderWater", 0);

	glCullFace(GL_BACK);
	glDisable(GL_STENCIL_TEST);

	waterSurfaceFBO.disable();

	shaderManager->updateLightPositions(true);

	rootNode->render(camera.getWorldToView(), camera.getViewToClip());


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterSurfaceFBO.getTexture()->getTextureName());

	waterNode->render(camera.getWorldToView(), camera.getViewToClip());

	glDisable(GL_BLEND);
}

void Scene::renderID() {
	shaderManager->updateLightPositions();
	camera.renderID();
	skybox.renderID(camera.getWorldToViewNoTranslation(), camera.getViewToClip());
	rootNode->renderID(camera.getWorldToView(), camera.getViewToClip());
	waterNode->renderID(camera.getWorldToView(), camera.getViewToClip());
}
