#pragma once

#include "../mesh/AbstractMesh.h"
#include "../ShaderProgram.h"
#include "../Texture2D.h"
#include "AbstractNode.h"


class MeshNode : public AbstractNode {

private:
	// Mesh
	AbstractMesh* mesh;

	// Shader
	ShaderProgram shaderProgram;

	// Texture
	vector<Texture2D*> textures;

protected:
	// Rendering
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;

public:
    // Constructors/destructors
    MeshNode(const ShaderProgram& shaderProgram, AbstractMesh* mesh);
    virtual ~MeshNode() override;

	// PhongProperty
	PhongProperty* getMaterial() { return phongProperty; };
	void setMaterial(PhongProperty* prop) { phongProperty = prop; };

    // Texture
    void addTexture(Texture2D* texture);

};
