#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "mesh/Cube.h"
#include "nodes/MeshNode.h"
#include "nodes/Skybox.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"

using namespace std;


Skybox::Skybox(const ShaderProgram& shaderProgram, const std::shared_ptr<TextureCubeMap>& texture) {

	Cube* cube = new Cube(true);
	MeshNode* cubeMesh = new MeshNode(shaderProgram, cube);

	cubeMesh->addComponent(new IBODraw());
	cubeMesh->addComponent(new DisableDepthMasking());
	cubeMesh->addTexture(texture);

	children.push_back(cubeMesh);
}

void swap(Skybox& first, Skybox& second) {
	swap(static_cast<AbstractNode&>(first), static_cast<AbstractNode&>(second));
}
