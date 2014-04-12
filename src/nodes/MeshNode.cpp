#include "nodes/MeshNode.h"

using namespace glm;
using namespace std;


// Constructors/destructors
MeshNode::MeshNode(const ShaderProgram& program, const shared_ptr<AbstractMesh>& theMesh)
		: AbstractNode(), shaderProgram(program), mesh(theMesh) {
}

// Texture
void MeshNode::addTexture(const shared_ptr<Texture>& texture) {
	shaderProgram.setTextureId(textures.size());
	textures.push_back(texture);
}

// Phong
void MeshNode::setMaterialProperty(const PhongProperty& phong) const {
	shaderProgram.setMaterialProperty(phong);
}

// Rendering
void MeshNode::renderSelf(const mat4& worldToView, const mat4& viewToClip) {
	for (const auto& component : components) {
		component->preRender(mesh, viewToClip, worldToView, objectToWorld);
	}

	shaderProgram.setObjectToWorld(objectToWorld);
	shaderProgram.setViewToClip(viewToClip);
	shaderProgram.setWorldToView(worldToView);

	for (size_t i = 0; i < textures.size(); ++i) {
		textures.at(i)->useAsTextureId(i);
	}

	for (const auto& component : components) {
		component->render(mesh);
	}

	for (const auto& component : components) {
		component->postRender();
	}
}

void MeshNode::renderIDSelf(const mat4& worldToView, const mat4& viewToClip) {
	shaderProgram.setUniformGLint("id", mesh->getId());
	renderSelf(worldToView, viewToClip);
	shaderProgram.setUniformGLint("id", 0);
}
