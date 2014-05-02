#include <memory>
#include "components/Blending.h"
#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "mesh/Cube.h"
#include "mesh/Quad.h"
#include "nodes/MeshNode.h"
#include "nodes/Skybox.h"
#include "LightProperties.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"
#include "OGFConfig.h"

using namespace std;


Skybox::Skybox(const ShaderProgram& skyboxShader, const ShaderProgram& lightShader, const shared_ptr<TextureCubeMap>& texture) {

	shared_ptr<Cube> cubeMesh(make_shared<Cube>(true));
	shared_ptr<Quad> quadMesh(make_shared<Quad>());

	shared_ptr<IBODraw> iboDraw(make_shared<IBODraw>());
	shared_ptr<DisableDepthMasking> disableDepthMasking(make_shared<DisableDepthMasking>());
	shared_ptr<Blending> blending(make_shared<Blending>());

	shared_ptr<MeshNode> cubeNode(make_shared<MeshNode>(skyboxShader, cubeMesh));

	cubeNode->addComponent(iboDraw);
	cubeNode->addComponent(disableDepthMasking);
	cubeNode->addTexture(texture);

	std::string resourceBase(OGF_RESOURCE_DIR);
	string textureDir = resourceBase + "/textures/";
	shared_ptr<Texture> glow(make_shared<Texture2D>(textureDir + "glow.png"));
	shared_ptr<Texture> sky(make_shared<Texture2D>(textureDir + "sky.png"));
	shared_ptr<Texture> sun(make_shared<Texture2D>(textureDir + "sun.png"));

	cubeNode->addTexture(sky);
	cubeNode->addTexture(glow);

	sunLightNode = make_shared<LightNode>(LightProperties::SUNLIGHT);
	sunLightNode->move(10000.0f, 0.0f, 0.0f);
	sunLightNode->disableParentTransformation(AbstractNode::ROTATION_SELF);

	sunNode = make_shared<MeshNode>(lightShader, quadMesh);
	sunNode->addComponent(iboDraw);
	sunNode->addComponent(disableDepthMasking);
	sunNode->addComponent(blending);
	sunNode->addTexture(sun);
	sunNode->move(5.0f, 0.0f, 0.0f);
	sunNode->rotateAroundSelfY(-90.0f);
	sunNode->add(sunLightNode);

	children.push_back(cubeNode);
	children.push_back(sunNode);
}
