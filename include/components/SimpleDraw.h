#pragma once

#include "AbstractComponent.h"


class SimpleDraw : public AbstractComponent {

public:
	SimpleDraw() : AbstractComponent() {}
	virtual ~SimpleDraw() override {}

	virtual void preRender(AbstractMesh*, const mat4&, const mat4&, const mat4&) override {}
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}
};
