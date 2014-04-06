#include "nodes/LightNode.h"
#include "ShaderManager.h"

using namespace glm;


LightNode::LightNode(ShaderManager* sManager,
	PhongProperty* lightProperty) : AbstractNode(), shaderManager(sManager) {
	phongProperty = lightProperty;
    lightId = shaderManager->add(this);
}

LightNode::LightNode(const LightNode& other) : AbstractNode(other), shaderManager(new ShaderManager(*other.shaderManager)), lightId(other.lightId) {
}

void LightNode::renderSelf(const mat4&, const mat4&) {
	shaderManager->updatePosition(lightId);
}

void LightNode::renderIDSelf(const mat4& worldToView, const mat4& viewToClip) {
	renderSelf(worldToView, viewToClip);
}
