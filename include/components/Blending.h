#pragma once

#include "AbstractComponent.h"


class Blending : public AbstractComponent {

public:
	Blending() : AbstractComponent() {}

	// Virtual constructor idiom
	virtual Blending* clone() const override { return new Blending(*this); }

	virtual ~Blending() override {}

	virtual void preRender(AbstractMesh* mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(AbstractMesh*) override {}
	virtual void postRender() override;
};
