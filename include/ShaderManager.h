#pragma once

#include <vector>
#include <glmhppnowarnings.h>
#include "ShaderProgram.h"

// M� fordward declare LightNode for � unng� sirkuler avhengighet
class LightNode;
class ShaderManager {

public:
	ShaderManager() {}

	int add(LightNode* light);
	void add(ShaderProgram& shader);
	int getNumberOfLights();
	int getNumberOfShaders();

	void updatePosition(int lightId);
	void setUniformGLint(const std::string& variable, const int value);

private:
	std::vector<ShaderProgram> shaders;
	std::vector<LightNode*> lights;
};
