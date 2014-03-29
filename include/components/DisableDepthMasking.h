#pragma once

#include "AbstractComponent.h"


class DisableDepthMasking : public AbstractComponent {

public:
	DisableDepthMasking() : AbstractComponent() {}
	virtual ~DisableDepthMasking() override {}

	virtual void preRender(AbstractMesh* mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(AbstractMesh*) override {}
	virtual void postRender() override;
};
