#pragma once
#include "AbstractNode.h"

// Må forward declare ShaderManager for å unngå sirkuler avhengighet
class ShaderManager;
class LightNode : public AbstractNode {

private:
	ShaderManager* shaderManager;
	int lightId;

protected:
	// Rendering
	virtual void renderThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	virtual void renderIDThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;

public:
	LightNode(ShaderManager* shaderManager, PhongProperty* lightProperty);
	virtual ~LightNode() override {}

	// Rendering
	//virtual void render(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	//virtual void renderID(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
};
