#pragma once

#include <glmhppnowarnings.h>
#include "../mesh/AbstractMesh.h"


class AbstractComponent {

public:
	virtual ~AbstractComponent() {}

	virtual void preRender(AbstractMesh* mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) = 0;
	virtual void render(AbstractMesh* mesh) = 0;
	virtual void postRender() = 0;

protected:
	AbstractComponent() {}
};
