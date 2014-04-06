#pragma once

#include "AbstractNode.h"

// M� forward declare ShaderManager for � unng� sirkuler avhengighet
class ShaderManager;

class LightNode : public AbstractNode {

public:
	explicit LightNode(ShaderManager* shaderManager, PhongProperty* lightProperty);
	LightNode(const LightNode& other);

	// Virtual constructor idiom
	virtual LightNode* clone() const override { return new LightNode(*this); }

	virtual ~LightNode() override {}

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;

private:
	ShaderManager* shaderManager;
	int lightId;

};
