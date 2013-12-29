#pragma once

#include <glmhppnowarnings.h>
#include "../mesh/AbstractMesh.h"

using namespace glm;


class AbstractComponent {

public:
	virtual ~AbstractComponent() {}

	virtual void preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) = 0;
	virtual void render(AbstractMesh* mesh) = 0;
	virtual void postRender() = 0;

protected:
	AbstractComponent() {}
};
