#pragma once

#include <memory>
#include <GL/glew.h>
#include "nodes/MeshNode.h"
#include "nodes/Camera.h"
#include "nodes/Skybox.h"
#include "FrameBuffer.h"
#include "ShaderManager.h"


class Scene {

public:
    explicit Scene(const Skybox& skybox, ShaderManager* sManager, const int width, const int height);

	void setRootNode(const std::shared_ptr<MeshNode>& node) { rootNode = node; }
	void setWaterNode(const std::shared_ptr<MeshNode>& node);
	void setCameraPosition(const glm::vec3& position);
	Camera& getCamera() { return camera; }
	Skybox& getSkybox() { return skybox; }

	void updateWindowDimensions(const int width, const int height);

    void render();
	void renderID();

private:
	std::shared_ptr<MeshNode> rootNode;
	std::shared_ptr<MeshNode> waterNode;
	Camera camera;
	ShaderManager* shaderManager;
	Skybox skybox;

	FrameBuffer waterSurfaceFBO;
};
