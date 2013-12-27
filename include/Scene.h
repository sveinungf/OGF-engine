#pragma once

#include <GL/glew.h>
#include "nodes/AbstractNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"


class Scene {

public:
    Scene();
    ~Scene();

	void setRootNode(AbstractNode *node);
	void setCamera(Camera* cam);
	void setCameraPosition(vec4 position);
	void addSkybox();
	Camera* getCamera();
    void render();
	void renderID();

private:
	AbstractNode* rootNode;
	Camera* camera;
	Skybox* skybox;
};
