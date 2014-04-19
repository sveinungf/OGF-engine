#pragma once

#include "AbstractComponent.h"


class StencilPlane : public AbstractComponent {

public:
	StencilPlane() : AbstractComponent() {}
	virtual ~StencilPlane() override {}

	// Virtual constructor idiom
	virtual StencilPlane* clone() const override { return new StencilPlane(*this); }

	virtual void preRender(const std::shared_ptr<AbstractMesh>& mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(const std::shared_ptr<AbstractMesh>&) override {}
	virtual void postRender() override;
};
