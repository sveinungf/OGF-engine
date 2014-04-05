#include "components/DisableDepthMasking.h"
#include "components/IBODraw.h"
#include "mesh/Cube.h"
#include "nodes/MeshNode.h"
#include "nodes/Skybox.h"
#include "OGFConfig.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"

using namespace std;


Skybox::Skybox() {
	string resourceBase(OGF_RESOURCE_DIR);
	
	ShaderProgram skyboxShader;
	skyboxShader << Shader(resourceBase + "/shaders/vSkybox.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fSkybox.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;

	Cube* cube = new Cube(true);
	MeshNode* cubeMesh = new MeshNode(skyboxShader, cube);

	cubeMesh->addComponent(new IBODraw());
	cubeMesh->addComponent(new DisableDepthMasking());

	vector<string> skyboxImages;
	skyboxImages.push_back(resourceBase + "/skyboxes/right.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/left.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/top.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/bottom.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/front.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/back.bmp");

	cubeMesh->addTexture(new TextureCubeMap(skyboxImages));

	children.push_back(cubeMesh);
}
