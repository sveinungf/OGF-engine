#pragma once

#include "../mesh/AbstractMesh.h"
#include "../ShaderProgram.h"
#include "../Texture2D.h"
#include "AbstractNode.h"


class MeshNode : public AbstractNode {

public:
    // Constructors/destructors
    explicit MeshNode(const ShaderProgram& shaderProgram, AbstractMesh* mesh);
    virtual ~MeshNode() override;

	// PhongProperty
	PhongProperty* getMaterial() { return phongProperty; };
	void setMaterial(PhongProperty* prop) { phongProperty = prop; };

    // Texture
    void addTexture(Texture2D* texture);

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
	std::vector<Texture2D*> textures;
};
