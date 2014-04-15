#include "ShaderManager.h"
#include "nodes/LightNode.h"

using namespace glm;
using namespace std;


void ShaderManager::addLight(const shared_ptr<LightNode>& light) {
	size_t lightId = lights.size();
	lights.push_back(light);

	for (const ShaderProgram& shader : shaders) {
		shader.setLightProperty(light->getLightProperty(), light->getPositionVec4(), lightId);
		shader.setUniformGLint("numberOfLights", lights.size());
	}
}

void ShaderManager::addShader(const ShaderProgram& shader) {
	size_t numberOfLights = lights.size();
	shaders.push_back(shader);

	shader.setUniformGLint("numberOfLights", numberOfLights);

	for (size_t l = 0; l < numberOfLights; ++l) {
		shader.setLightProperty(lights[l]->getLightProperty(), lights[l]->getPositionVec4(), l);
	}
}

void ShaderManager::updateLightPositions(const bool flipped) const {
	for (size_t i = 0; i < lights.size(); ++i) {
		vec4 lightPosition = lights[i]->getPositionVec4();
		if (flipped) {
			lightPosition.y = -lightPosition.y;
		}

		for (const ShaderProgram& shader : shaders) {
			shader.setLightPosition(lightPosition, i);
		}
	}
}

void ShaderManager::setUniformGLint(const string& variable, const int value) const {
	for (const ShaderProgram& shader : shaders){
		shader.setUniformGLint(variable, value);
	}
}
