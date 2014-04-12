#pragma once

#include <memory>
#include "AbstractNode.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"


class Skybox : public AbstractNode {

public:
	explicit Skybox(const ShaderProgram& shaderProgram, const std::shared_ptr<TextureCubeMap>& texture);
	Skybox(const Skybox&) = default;
	Skybox(Skybox&& other) { swap(*this, other); }
	virtual ~Skybox() override {}

	// Virtual constructor idiom
	virtual Skybox* clone() const override { return new Skybox(*this); }

	friend void swap(Skybox& first, Skybox& second);

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}
};
