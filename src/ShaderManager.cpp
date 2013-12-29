#include "ShaderManager.h"
#include "nodes/LightNode.h"


int ShaderManager::add(LightNode* light) {
	int lightId = lights.size();
	lights.push_back(light);

	for (unsigned int s = 0; s < shaders.size(); s++) {
		shaders[s].setLightProperty(*light->getPhongProperty(), light->getPositionVec4(), lightId);
		shaders[s].setUniformGLint("numberOfLights", lights.size());
	};
	return lightId;
}

void ShaderManager::add(ShaderProgram& shader) {
	shaders.push_back(shader);
	if (lights.size() > 0) {
		for (unsigned int l = 0; l < lights.size(); l++) {
			shader.setLightProperty(*lights[l]->getPhongProperty(), lights[l]->getPositionVec4(), l);
			shader.setUniformGLint("numberOfLights", lights.size());
		}
	}
}

void ShaderManager::updatePosition(int lightId) {
	for (unsigned int s = 0; s < shaders.size(); s++) {
		shaders[s].setLightPosition(lights[lightId]->getPositionVec4(), lightId);
	}
}

int ShaderManager::getNumberOfLights() {
	return lights.size();
}

int ShaderManager::getNumberOfShaders() {
	return shaders.size();
}

void ShaderManager::setUniformGLint(const string& variable, const int value) {
	for (ShaderProgram shader : shaders){
		shader.setUniformGLint(variable, value);
	}
}
