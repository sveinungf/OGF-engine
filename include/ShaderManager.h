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
	void add(const ShaderProgram& shader);
	int getNumberOfLights() const { return lights.size(); }
	int getNumberOfShaders() const { return shaders.size(); }

	void updatePosition(const int lightId) const;
	void setUniformGLint(const std::string& variable, const int value) const;

private:
	std::vector<ShaderProgram> shaders;
	std::vector<LightNode*> lights;
};
