#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "mesh/Cube.h"
#include "nodes/MeshNode.h"
#include "nodes/Skybox.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"

using namespace std;


Skybox::Skybox(const ShaderProgram& shaderProgram, const shared_ptr<TextureCubeMap>& texture) {

	shared_ptr<Cube> cubeMesh(make_shared<Cube>(true));
	shared_ptr<MeshNode> cubeNode(make_shared<MeshNode>(shaderProgram, cubeMesh));

	cubeNode->addComponent(make_shared<IBODraw>());
	cubeNode->addComponent(make_shared<DisableDepthMasking>());
	cubeNode->addTexture(texture);

	children.push_back(cubeNode);
}
