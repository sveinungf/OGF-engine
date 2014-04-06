#pragma once

#include <GL/glew.h>
#include "nodes/AbstractNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"


class Scene {

public:
    explicit Scene(const Skybox& skybox);
    ~Scene();

	void setRootNode(AbstractNode* const node) { rootNode = node; }
	void setCameraPosition(const glm::vec3& position);
	Camera& getCamera() { return camera; }

    void render();
	void renderID();

private:
	AbstractNode* rootNode;
	Camera camera;
	Skybox skybox;
};
