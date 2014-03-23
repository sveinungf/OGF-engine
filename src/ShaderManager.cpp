#include "ShaderManager.h"
#include "nodes/LightNode.h"

using namespace glm;
using namespace std;


int ShaderManager::add(LightNode* light) {
	int lightId = lights.size();
	lights.push_back(light);

	for (unsigned int s = 0; s < shaders.size(); s++) {
		shaders[s].setLightProperty(*light->getPhongProperty(), light->getPositionVec4(), lightId);
		shaders[s].setUniformGLint("numberOfLights", lights.size());
	};
	return lightId;
}

void ShaderManager::add(const ShaderProgram& shader) {
	
	unsigned int numberOfLights = lights.size();
	shader.setUniformGLint("numberOfLights", numberOfLights);

	//if (lights.size() > 0) {
		for (unsigned int l = 0; l < numberOfLights; ++l) {
			shader.setLightProperty(*lights[l]->getPhongProperty(), lights[l]->getPositionVec4(), l);
		}
	//}

	shaders.push_back(shader);
}

void ShaderManager::updatePosition(const int lightId) const {
	const vec4& lightPosition = lights[lightId]->getPositionVec4();

	for (const ShaderProgram& shader : shaders) {
		shader.setLightPosition(lightPosition, lightId);
	}
}

void ShaderManager::setUniformGLint(const string& variable, const int value) const {
	for (const ShaderProgram& shader : shaders){
		shader.setUniformGLint(variable, value);
	}
}
