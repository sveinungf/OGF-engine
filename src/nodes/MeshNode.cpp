#include "nodes/MeshNode.h"


// Constructors/destructors
MeshNode::MeshNode(const ShaderProgram& program,
           AbstractMesh* meshAbstract) : AbstractNode(), shaderProgram(program), mesh(meshAbstract) {
}

MeshNode::~MeshNode() {
	delete mesh;
}

// Texture
void MeshNode::addTexture(Texture2D* texture) {
	shaderProgram.setTextureId(textures.size());
	textures.push_back(texture);
}

// Rendering
void MeshNode::renderThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	updateObjectToWorld(parentTransformations);

	for (AbstractComponent * component : components) {
		component->preRender(mesh, viewToClip, worldToView, objectToWorld);
	}

	shaderProgram.setObjectToWorld(objectToWorld);
	shaderProgram.setViewToClip(viewToClip);
	shaderProgram.setWorldToView(worldToView);

	for (unsigned int i = 0; i < textures.size(); ++i) {
		textures.at(i)->useAsTextureId(i);
	}

	if (phongProperty != nullptr) {
		shaderProgram.setMaterialProperty(*phongProperty);
	}

	for (AbstractComponent * component : components) {
		component->render(mesh);
	}

	for (AbstractComponent * component : components) {
		component->postRender();
	}
}

void MeshNode::renderIDThis(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	shaderProgram.setUniformGLint("id", mesh->getId());
	renderThis(worldToView, viewToClip, parentTransformations);
	shaderProgram.setUniformGLint("id", 0);
}
