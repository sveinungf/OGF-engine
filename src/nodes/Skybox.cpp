#include <memory>
#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "components/SimpleDraw.h"
#include "mesh/Cube.h"
#include "mesh/Sphere.h"
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
	shared_ptr<Sphere> sphereMesh(make_shared<Sphere>());

	shared_ptr<MeshNode> cubeNode(make_shared<MeshNode>(skyboxShader, cubeMesh));

	cubeNode->addComponent(make_shared<IBODraw>());
	cubeNode->addComponent(make_shared<DisableDepthMasking>());
	cubeNode->addTexture(texture);

	std::string resourceBase(OGF_RESOURCE_DIR);
	string textureDir = resourceBase + "/textures/";
	shared_ptr<Texture> glow(make_shared<Texture2D>(textureDir + "glow.png"));
	shared_ptr<Texture> sky(make_shared<Texture2D>(textureDir + "sky.png"));

	cubeNode->addTexture(sky);
	cubeNode->addTexture(glow);

	sunLightNode = make_shared<LightNode>(LightProperties::SUNLIGHT);

	sunNode = make_shared<MeshNode>(lightShader, sphereMesh);
	sunNode->addComponent(make_shared<SimpleDraw>());
	sunNode->move(200.0f, 0.0f, 0.0f);
	sunNode->add(sunLightNode);

	children.push_back(cubeNode);
	children.push_back(sunNode);
}
