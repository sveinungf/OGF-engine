#pragma once

#include "AbstractNode.h"


class LightNode : public AbstractNode {

public:
	explicit LightNode(PhongProperty* lightProperty) : AbstractNode() { phongProperty = lightProperty; }

	// Virtual constructor idiom
	virtual LightNode* clone() const override { return new LightNode(*this); }

	virtual ~LightNode() override {}

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}
};
