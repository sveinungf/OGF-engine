#pragma once

#include <memory>
#include "../mesh/AbstractMesh.h"
#include "../ShaderProgram.h"
#include "../Texture.h"
#include "AbstractNode.h"


class MeshNode : public AbstractNode {

public:
    explicit MeshNode(const ShaderProgram& shaderProgram, const std::shared_ptr<AbstractMesh>& mesh);
	virtual ~MeshNode() override {}

	// Virtual constructor idiom
	virtual MeshNode* clone() const override { return new MeshNode(*this); }

	// Shader
	const ShaderProgram& getShaderProgram() const { return shaderProgram; }

    // Texture
    void addTexture(const std::shared_ptr<Texture>& texture);

	// Phong
	void setMaterialProperty(const PhongProperty& phong) const;

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;

private:
	// Shader
	ShaderProgram shaderProgram;

	// Mesh
	std::shared_ptr<AbstractMesh> mesh;

	// Texture
	std::vector<std::shared_ptr<Texture>> textures;
};
