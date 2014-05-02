#pragma once

#include <memory>
#include "AbstractNode.h"
#include "LightNode.h"
#include "MeshNode.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"


class Skybox : public AbstractNode {

public:
	explicit Skybox(const ShaderProgram& skyboxShader, const ShaderProgram& lightShader, const std::shared_ptr<TextureCubeMap>& texture);
	virtual ~Skybox() override {}

	// Virtual constructor idiom
	virtual Skybox* clone() const override { return new Skybox(*this); }

	const std::shared_ptr<LightNode>& getSunLightNode() { return sunLightNode; }
	const std::shared_ptr<MeshNode>& getSunNode() { return sunNode; }

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}

private:
	std::shared_ptr<LightNode> sunLightNode;
	std::shared_ptr<MeshNode> sunNode;
};
