#pragma once

#include <GL/glew.h>
#include "nodes/AbstractNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"


class Scene {

public:
    Scene();
    ~Scene();

	void init();
	void setRootNode(AbstractNode* node) { rootNode = node; }
	void setCameraPosition(const vec3& position);
	Camera* getCamera() { return camera; }
    void render();
	void renderID();

private:
	AbstractNode* rootNode;
	Camera* camera;
	Skybox* skybox;
};
