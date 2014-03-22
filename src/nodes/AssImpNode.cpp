#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/version.h>
#include "mesh/AssImpMesh.h"
#include "nodes/AssImpNode.h"
#include "nodes/MeshNode.h"

using namespace glm;


AssImpNode::AssImpNode(const ShaderProgram& program, const std::string& path){
	auto importer = Assimp::Importer();
	const aiScene* mdl = importer.ReadFile(path, aiProcess_Triangulate);

	if (mdl == nullptr){
		std::cout << path << " is an invalid model!" << std::endl;
		return;
	}

	std::cout << std::endl << "Assembling using assImp v" << ASSIMP_API::aiGetVersionMajor() << "." <<
		ASSIMP_API::aiGetVersionMinor() << ":" << std::endl;
	std::cout << "  Path: " << path << std::endl;

	for (unsigned int i = 0; i < mdl->mNumMeshes; i++){
		std::cout << "  Mesh " << i << ": ";
		AssImpMesh* mesh = new AssImpMesh(mdl->mMeshes[i]);
		MeshNode* m = new MeshNode(program, mesh);
		self.push_back(m);
	}
	std::cout << std::endl;
}

AssImpNode::~AssImpNode(){
	for (MeshNode * node : self) {
		delete node;
	}
}

void AssImpNode::addComponent(AbstractComponent* component, int mesh) {
	if (mesh < 0) {
		for (MeshNode * child : self) {
			child->addComponent(component);
		}
	} else if (mesh < (int) self.size()) {
		self.at(mesh)->addComponent(component);
	}
}

void AssImpNode::setMaterial(PhongProperty* material, int mesh) {
	if (mesh < 0){
		for (MeshNode * child : self) {
			child->setMaterial(material);
		}
	} else if(mesh < (int) self.size()) {
		self.at(mesh)->setMaterial(material);
	}
}

void AssImpNode::addTexture(Texture2D* texture, int mesh) {
	if (mesh < 0){
		for (MeshNode * child : self) {
			child->addTexture(texture);
		}
	} else if (mesh < (int) self.size()) {
		self.at(mesh)->addTexture(texture);
	}
}

void AssImpNode::renderSelf(const mat4& worldToView, const mat4& viewToClip) {
	for (AbstractNode * child : self) {
		child->render(worldToView, viewToClip, transformations);
	}
}

void AssImpNode::renderIDSelf(const mat4& worldToView, const mat4& viewToClip) {
	for (AbstractNode * child : self) {
		child->renderID(worldToView, viewToClip, transformations);
	}
}
