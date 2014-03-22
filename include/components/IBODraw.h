#pragma once

#include "AbstractComponent.h"


class IBODraw : public AbstractComponent {

public:
	IBODraw() : AbstractComponent() {}
	virtual ~IBODraw() override {}

	virtual void preRender(AbstractMesh*, const glm::mat4&, const glm::mat4&, const glm::mat4&) override {}
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}
};
