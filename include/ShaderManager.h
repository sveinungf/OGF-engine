#pragma once
#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm\glm.hpp>
#pragma warning(pop)
#include <vector>
#include "ShaderProgram.h"

// Må fordward declare LightNode for å unngå sirkuler avhengighet
class LightNode;
class ShaderManager {

public:
	ShaderManager();
	~ShaderManager();

	int add(LightNode* light);
	void add(ShaderProgram& shader);
	int getNumberOfLights();
	int getNumberOfShaders();

	void updatePosition(int lightId);
	void setUniformGLint(const string& variable, const int value);

private:
	std::vector<ShaderProgram> shaders;
	std::vector<LightNode*> lights;
};
