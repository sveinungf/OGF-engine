#pragma once

#include "AbstractComponent.h"


class IBODraw : public AbstractComponent {

public:
	IBODraw() : AbstractComponent() {}
	virtual ~IBODraw() override {}

	// Virtual constructor idiom
	virtual IBODraw* clone() const override { return new IBODraw(*this); }

	virtual void preRender(const std::shared_ptr<AbstractMesh>&, const glm::mat4&, const glm::mat4&, const glm::mat4&) override {}
	virtual void render(const std::shared_ptr<AbstractMesh>& mesh) override;
	virtual void postRender() override {}
};
