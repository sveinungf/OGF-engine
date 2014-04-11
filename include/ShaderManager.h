#pragma once

#include <vector>
#include <glmhppnowarnings.h>
#include "nodes/LightNode.h"
#include "ShaderProgram.h"


class ShaderManager {

public:
	ShaderManager() {}

	void addLight(LightNode* light);
	void addShader(const ShaderProgram& shader);

	void updateLightPositions() const;
	void setUniformGLint(const std::string& variable, const int value) const;

private:
	std::vector<ShaderProgram> shaders;
	std::vector<LightNode*> lights;
};
