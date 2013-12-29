#pragma once

#include "AbstractNode.h"

// M� forward declare ShaderManager for � unng� sirkuler avhengighet
class ShaderManager;

class LightNode : public AbstractNode {

public:
	LightNode(ShaderManager* shaderManager, PhongProperty* lightProperty);
	virtual ~LightNode() override {}

protected:
	// Rendering
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip) override;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip) override;

private:
	ShaderManager* shaderManager;
	int lightId;

};
