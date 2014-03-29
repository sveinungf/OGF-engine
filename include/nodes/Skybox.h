#pragma once

#include "AbstractNode.h"


class Skybox : public AbstractNode {

public:
	Skybox();
	virtual ~Skybox() override {}

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}
};
