#pragma once

#include <memory>
#include "../mesh/AbstractMesh.h"
#include "../ShaderProgram.h"
#include "../Texture.h"
#include "AbstractNode.h"


class MeshNode : public AbstractNode {

public:
    // Constructor
    explicit MeshNode(const ShaderProgram& shaderProgram, AbstractMesh* const mesh);
	MeshNode(const MeshNode& other);

	// Virtual constructor idiom
	virtual MeshNode* clone() const override { return new MeshNode(*this); }

	// Destructor
    virtual ~MeshNode() override;

    // Texture
    void addTexture(const std::shared_ptr<Texture>& texture);

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;

private:
	// Shader
	ShaderProgram shaderProgram;

	// Mesh
	AbstractMesh* mesh;

	// Texture
	std::vector<std::shared_ptr<Texture>> textures;
};
