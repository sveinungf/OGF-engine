#pragma once

#include <memory>
#include "AbstractNode.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"


class Skybox : public AbstractNode {

public:
	explicit Skybox(const ShaderProgram& shaderProgram, const std::shared_ptr<TextureCubeMap>& texture);

	// Virtual constructor idiom
	virtual Skybox* clone() const override { return new Skybox(*this); }

	virtual ~Skybox() override {}

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}
};
