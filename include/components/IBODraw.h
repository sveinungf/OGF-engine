#pragma once

#include "AbstractComponent.h"


class IBODraw : public AbstractComponent {

public:
	IBODraw() : AbstractComponent() {}
	virtual ~IBODraw() override {}

	// Virtual constructor idiom
	virtual IBODraw* clone() const override { return new IBODraw(*this); }

	virtual void preRender(AbstractMesh*, const glm::mat4&, const glm::mat4&, const glm::mat4&) override {}
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}
};
