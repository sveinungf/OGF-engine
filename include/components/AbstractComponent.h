#pragma once

#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm/glm.hpp>
#pragma warning(pop)
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
