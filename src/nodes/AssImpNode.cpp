#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/version.h>
#include "mesh/AssImpMesh.h"
#include "nodes/AssImpNode.h"
#include "nodes/MeshNode.h"

using namespace glm;
using namespace std;


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
		shared_ptr<AssImpMesh> mesh(make_shared<AssImpMesh>(mdl->mMeshes[i]));
		MeshNode meshNode(program, mesh);
		self.push_back(meshNode);
	}

	std::cout << std::endl;
}

void AssImpNode::addComponent(const shared_ptr<AbstractComponent>& component, const int mesh) {
	if (mesh < 0) {
		for (MeshNode& child : self) {
			child.addComponent(component);
		}
	} else if (mesh < (int) self.size()) {
		self.at(mesh).addComponent(component);
	}
}

void AssImpNode::setMaterial(const PhongProperty& material, const int mesh) {
	if (mesh < 0) {
		for (MeshNode& child : self) {
			child.setMaterialProperty(material);
		}
	} else if(mesh < (int) self.size()) {
		self.at(mesh).setMaterialProperty(material);
	}
}

void AssImpNode::addTexture(const std::shared_ptr<Texture>& texture, const int mesh) {
	if (mesh < 0) {
		for (MeshNode& child : self) {
			child.addTexture(texture);
		}
	} else if (mesh < (int) self.size()) {
		self.at(mesh).addTexture(texture);
	}
}

void AssImpNode::renderSelf(const mat4& worldToView, const mat4& viewToClip) {
	for (MeshNode& child : self) {
		child.render(worldToView, viewToClip, transformations);
	}
}

void AssImpNode::renderIDSelf(const mat4& worldToView, const mat4& viewToClip) {
	for (MeshNode& child : self) {
		child.renderID(worldToView, viewToClip, transformations);
	}
}
