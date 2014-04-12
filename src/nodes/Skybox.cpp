#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "mesh/Cube.h"
#include "nodes/MeshNode.h"
#include "nodes/Skybox.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"

using namespace std;


Skybox::Skybox(const ShaderProgram& shaderProgram, const std::shared_ptr<TextureCubeMap>& texture) {

	Cube* cubeMesh = new Cube(true);
	shared_ptr<MeshNode> cubeNode(make_shared<MeshNode>(shaderProgram, cubeMesh));

	cubeNode->addComponent(make_shared<IBODraw>());
	cubeNode->addComponent(make_shared<DisableDepthMasking>());
	cubeNode->addTexture(texture);

	children.push_back(cubeNode);
}

void swap(Skybox& first, Skybox& second) {
	swap(static_cast<AbstractNode&>(first), static_cast<AbstractNode&>(second));
}
