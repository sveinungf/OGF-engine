#pragma once

#include <memory>
#include <vector>
#include <glmhppnowarnings.h>
#include "nodes/LightNode.h"
#include "ShaderProgram.h"


class ShaderManager {

public:
	ShaderManager() {}

	void addLight(const std::shared_ptr<LightNode>& light);
	void addShader(const ShaderProgram& shader);

	void updateLightPositions(const bool flipped = false) const;
	void setUniformGLint(const std::string& variable, const int value) const;

private:
	std::vector<ShaderProgram> shaders;
	std::vector<std::shared_ptr<LightNode>> lights;
};
