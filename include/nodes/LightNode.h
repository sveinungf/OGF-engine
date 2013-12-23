#pragma once
#include "AbstractNode.h"

// M� forward declare ShaderManager for � unng� sirkuler avhengighet
class ShaderManager;
class LightNode : public AbstractNode {

private:
	ShaderManager* shaderManager;
	int lightId;

protected:
	// Rendering
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;

public:
	LightNode(ShaderManager* shaderManager, PhongProperty* lightProperty);
	virtual ~LightNode() override {}

	// Rendering
	//virtual void render(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	//virtual void renderID(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
};
