#pragma once

#include "AbstractNode.h"


class LightNode : public AbstractNode {

public:
	explicit LightNode(const PhongProperty& phong) : AbstractNode(), lightProperty(phong) {}
	virtual ~LightNode() override {}

	// Virtual constructor idiom
	virtual LightNode* clone() const override { return new LightNode(*this); }

	const PhongProperty& getLightProperty() const { return lightProperty; }

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}

private:
	PhongProperty lightProperty;
};
