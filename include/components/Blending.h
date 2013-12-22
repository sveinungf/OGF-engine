#pragma once

#include "AbstractComponent.h"

#pragma warning(push)
#pragma warning(disable:4100) // ignore unused parameters

class Blending : public AbstractComponent {

public:
	Blending() {};

	virtual void preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) override;
	virtual void render(AbstractMesh* mesh) override {}
	virtual void postRender() override;
};

#pragma warning(pop)
