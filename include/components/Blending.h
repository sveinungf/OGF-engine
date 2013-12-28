#pragma once

#include "AbstractComponent.h"


class Blending : public AbstractComponent {

public:
	Blending() : AbstractComponent() {}
	virtual ~Blending() override {}

	virtual void preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) override;
	virtual void render(AbstractMesh*) override {}
	virtual void postRender() override;
};
