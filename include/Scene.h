#pragma once

#include <memory>
#include <GL/glew.h>
#include "nodes/AbstractNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"
#include "ShaderManager.h"


class Scene {

public:
    explicit Scene(const Skybox& skybox, ShaderManager* sManager);

	void setRootNode(const std::shared_ptr<AbstractNode>& node) { rootNode = node; }
	void setWaterNode(const std::shared_ptr<AbstractNode>& node) { waterNode = node; }
	void setCameraPosition(const glm::vec3& position);
	Camera& getCamera() { return camera; }

    void render();
	void renderID();

private:
	std::shared_ptr<AbstractNode> rootNode;
	std::shared_ptr<AbstractNode> waterNode;
	Camera camera;
	ShaderManager* shaderManager;
	Skybox skybox;
};
