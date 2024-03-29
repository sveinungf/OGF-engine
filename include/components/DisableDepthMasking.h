#pragma once

#include "AbstractComponent.h"


class DisableDepthMasking : public AbstractComponent {

public:
	DisableDepthMasking() : AbstractComponent() {}
	virtual ~DisableDepthMasking() override {}

	// Virtual constructor idiom
	virtual DisableDepthMasking* clone() const override { return new DisableDepthMasking(*this); }

	virtual void preRender(const std::shared_ptr<AbstractMesh>& mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(const std::shared_ptr<AbstractMesh>&) override {}
	virtual void postRender() override;
};
