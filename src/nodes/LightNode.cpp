#include "nodes/LightNode.h"
#include "ShaderManager.h"

LightNode::LightNode(ShaderManager* shaderManager,
	PhongProperty* lightProperty) : AbstractNode() {
	phongProperty = lightProperty;
    lightId = shaderManager->add(this);
    this->shaderManager = shaderManager;
};

void LightNode::renderSelf(const mat4&, const mat4&) {
	shaderManager->updatePosition(lightId);
}

void LightNode::renderIDSelf(const mat4& worldToView, const mat4& viewToClip) {
	renderSelf(worldToView, viewToClip);
}
