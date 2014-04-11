#pragma once

#include <GL/glew.h>
#include "nodes/AbstractNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"
#include "ShaderManager.h"


class Scene {

public:
    explicit Scene(const Skybox& skybox, ShaderManager* sManager);
    ~Scene();

	void setRootNode(AbstractNode* const node) { rootNode = node; }
	void setCameraPosition(const glm::vec3& position);
	Camera& getCamera() { return camera; }

    void render();
	void renderID();

private:
	AbstractNode* rootNode;
	Camera camera;
	ShaderManager* shaderManager;
	Skybox skybox;
};
