#pragma once

#include "AbstractComponent.h"


class IBODraw : public AbstractComponent {

public:
	IBODraw() : AbstractComponent() {}
	virtual ~IBODraw() override {}

	virtual void preRender(AbstractMesh*, const mat4&, const mat4&, const mat4&) override {}
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}
};
