#pragma once

#include "AbstractComponent.h"


class SimpleDraw : public AbstractComponent {

public:
	SimpleDraw() : AbstractComponent() {}

	// Virtual constructor idiom
	virtual SimpleDraw* clone() const override { return new SimpleDraw(*this); }

	virtual ~SimpleDraw() override {}

	virtual void preRender(AbstractMesh*, const glm::mat4&, const glm::mat4&, const glm::mat4&) override {}
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}
};
