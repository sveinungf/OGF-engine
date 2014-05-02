#include <iostream>
#include <memory>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glmhppnowarnings.h>
#include <glm/gtx/transform.hpp>

#include "components/Blending.h"
#include "components/IBODraw.h"
#include "components/Instancing.h"
#include "components/SimpleDraw.h"
#include "components/StencilPlane.h"
#include "components/SwitchableComponent.h"
#include "mesh/AssImpMesh.h"
#include "mesh/Cube.h"
#include "mesh/Quad.h"
#include "mesh/Sphere.h"
#include "mesh/Terrain.h"
#include "nodes/AssImpNode.h"
#include "nodes/LightNode.h"
#include "nodes/MeshNode.h"
#include "Debug.h"
#include "LightProperties.h"
#include "MaterialProperties.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "TerrainContentData.h"
#include "FrameBuffer.h"
#include "OGFConfig.h"
#include "TextureCubeMap.h"

using namespace glm;
using namespace std;


GLFWwindow* window;
const int width = 1280;
const int height = 720;

vec3 cameraStartPosition(0.0f, 60.0f, -10.0f);
double oldTimeSinceStart;
unsigned int frameCount;
double previousTime;

Scene* scene;
shared_ptr<AssImpNode> tree;
shared_ptr<AssImpNode> rock;
shared_ptr<MeshNode> grassNode;
shared_ptr<MeshNode> waterNode;
shared_ptr<MeshNode> terrain;
shared_ptr<Instancing> grassInstancing;
shared_ptr<Instancing> treeInstancing;
ShaderManager* sManager;

bool renderID = false;
bool fastSun = false;

void init() {
	oldTimeSinceStart = glfwGetTime();
	previousTime = oldTimeSinceStart;

	string resourceBase(OGF_RESOURCE_DIR);

	ShaderProgram instancingShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vInstancing.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fInstancing.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram waterShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vWater.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fWater.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram lightShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vLightShader.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fLightShader.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram terrainShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vTerrain.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fTerrain.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram treeShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vTree.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fTree.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram bumpMapShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vBumpMapLightshader.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fBumpMapLightshader.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;
	ShaderProgram skyboxShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vSkybox.glsl", Shader::VERTEX)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAGMENT)
		<< Shader(resourceBase + "/shaders/fSkybox.glsl", Shader::FRAGMENT)
		<< ShaderProgram::LINK;

	sManager = new ShaderManager();
	sManager->addShader(instancingShader);
	sManager->addShader(waterShader);
	sManager->addShader(lightShader);
	sManager->addShader(terrainShader);
	sManager->addShader(treeShader);
	sManager->addShader(bumpMapShader);
	sManager->addShader(skyboxShader);

	shared_ptr<Quad> quadMesh(make_shared<Quad>());
	
	shared_ptr<Terrain> terrainMesh(make_shared<Terrain>(resourceBase + "/heightmaps/heightmap.tga"));

	TerrainContentData contentData = terrainMesh->getContentData();
	terrainShader.setTerrainContentData(contentData);

	cout << "Grass instances: " << contentData.getGrassPositions().size() << endl;
	cout << "Tree instances: " << contentData.getTreePositions().size() << endl;

	shared_ptr<Blending> blending(make_shared<Blending>());
	shared_ptr<IBODraw> ibodraw(make_shared<IBODraw>());
	shared_ptr<SimpleDraw> simpleDraw(make_shared<SimpleDraw>());
	shared_ptr<StencilPlane> stencilPlane(make_shared<StencilPlane>());

	string textureDir = resourceBase + "/textures/";
	shared_ptr<Texture> grass(make_shared<Texture2D>(textureDir + "grass.bmp"));
	shared_ptr<Texture> sand(make_shared<Texture2D>(textureDir + "sand_diffuse.png"));
	shared_ptr<Texture> greyrock(make_shared<Texture2D>(textureDir + "rock4.png"));
	shared_ptr<Texture> snow(make_shared<Texture2D>(textureDir + "snow.bmp"));
	shared_ptr<Texture> billboardGrass(make_shared<Texture2D>(textureDir + "billboardgrass.png"));
	shared_ptr<Texture> twig(make_shared<Texture2D>(textureDir + "twig.png"));
	shared_ptr<Texture> bark(make_shared<Texture2D>(textureDir + "bark.png"));
	shared_ptr<Texture> rockNormalMap(make_shared<Texture2D>(textureDir + "S1Normal.jpg"));
	shared_ptr<Texture> rockDiffus(make_shared<Texture2D>(textureDir + "S3Diffus.jpg"));
	
	vector<string> skyboxImages;
	skyboxImages.push_back(resourceBase + "/skyboxes/night_right1.png");
	skyboxImages.push_back(resourceBase + "/skyboxes/night_left2.png");
	skyboxImages.push_back(resourceBase + "/skyboxes/night_top3.png");
	skyboxImages.push_back(resourceBase + "/skyboxes/night_bottom4.png");
	skyboxImages.push_back(resourceBase + "/skyboxes/night_front5.png");
	skyboxImages.push_back(resourceBase + "/skyboxes/night_back6.png");
	shared_ptr<TextureCubeMap> skyboxTexture(make_shared<TextureCubeMap>(skyboxImages));

	grassInstancing = make_shared<Instancing>(contentData.getGrassPositions(), contentData.getGrassNormals());
	grassNode = make_shared<MeshNode>(instancingShader, quadMesh);
	grassNode->addComponent(grassInstancing);
	grassNode->addComponent(blending);
	grassNode->addTexture(billboardGrass);
	grassNode->move(0.0f, 0.5f, 0.0f);
	
	shared_ptr<SwitchableComponent> waterSwitchComponent(make_shared<SwitchableComponent>());
	waterSwitchComponent->addComponent(stencilPlane);
	waterSwitchComponent->addComponent(blending);
	waterNode = make_shared<MeshNode>(waterShader, quadMesh);
	waterNode->addComponent(ibodraw);
	waterNode->addComponent(waterSwitchComponent);
	waterNode->rotateAroundSelfX(-90.0f);
	waterNode->scale((GLfloat) terrainMesh->getWidth(), (GLfloat) terrainMesh->getLength(), 1.0f);
	
	treeInstancing = make_shared<Instancing>(contentData.getTreePositions());
	tree = make_shared<AssImpNode>(treeShader, resourceBase + "/tree.3ds");
	tree->addComponent(treeInstancing);
	tree->addComponent(blending);
	tree->addTexture(twig, 0);
	tree->addTexture(bark, 1);
	tree->addTexture(bark, 2);
	tree->addTexture(bark, 3);
	
	rock = make_shared<AssImpNode>(bumpMapShader, resourceBase + "/Stone_Forest_1.obj");
	rock->addComponent(simpleDraw);
	rock->move(0.0f, 0.45f, 0.0f);
	rock->scale(0.02f, 0.02f, 0.02f);
	rock->move(vec3(terrainMesh->getPointAt(50, 50)));
	rock->addTexture(rockNormalMap);
	rock->addTexture(rockDiffus);

	terrain = make_shared<MeshNode>(terrainShader, terrainMesh);
	terrain->addComponent(ibodraw);
	terrain->addTexture(sand);
	terrain->addTexture(grass);
	terrain->addTexture(greyrock);
	terrain->addTexture(snow);
	terrain->add(grassNode);
	terrain->add(tree);
	terrain->add(rock);

	Skybox skybox(skyboxShader, lightShader, skyboxTexture);
	scene = new Scene(skybox, sManager, width, height);
	scene->getCamera().updateWindowDimensions(width, height);
	scene->setCameraPosition(cameraStartPosition);
	scene->setRootNode(terrain);
	scene->setWaterNode(waterNode);

	sManager->addLight(skybox.getSunLightNode());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void display(void) {
	double timeSinceStart = glfwGetTime();
	double deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	scene->getCamera().doMove(deltaTime);

	int factor = fastSun ? 15 : 1;
	scene->getSkybox().getSunNode()->rotateAroundOriginZ(factor * (float) deltaTime);

	double timeInterval = timeSinceStart - previousTime;
	if (timeInterval > 1.0) {
		double fps = frameCount / timeInterval;
		stringstream ss;
		ss << "OGF Engine program - FPS: " << fps;
		glfwSetWindowTitle(window, ss.str().c_str());
		previousTime = timeSinceStart;
		frameCount = 0;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (renderID) {
		sManager->setUniformGLint("idMul", 3425160);
		scene->renderID();
	} else {
		scene->render();
	}
	
	++frameCount;
}

void keyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case 'f':
		case 'F':
			fastSun = !fastSun;
			break;
		case 'l':
		case 'L':
			cout << "LIGHT POS: " << to_string(scene->getSkybox().getSunLightNode()->getPositionVec3()) << endl;
			break;
		case 'o':
		case 'O':
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// show wireframe
			break;
		case 'i':
		case 'I':
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// back to default
			break;
		case 'p':
		case 'P':
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);	// show points
			break;
		case 'u':
		case 'U':
			renderID = !renderID;
			break;
		case 'g':
		case 'G':
			std::cout << "GRESS: " << grassInstancing->getVisibleInstances() << std::endl;
			break;
		case 't':
		case 'T':
			std::cout << "Trees: " << treeInstancing->getVisibleInstances() << std::endl;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			scene->getCamera().keyDown(key);
			break;
		}
	} else if (action == GLFW_RELEASE) {
		scene->getCamera().keyUp(key);
	}
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	scene->getCamera().mouseActive(window, (int) xpos, (int) ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/) {
	scene->getCamera().mouseAction(window, button, action);

	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_MIDDLE: {
				double cursorX, cursorY;
				int windowWidth, windowHeight;
				unsigned char data[4] = {0};

				glfwGetCursorPos(window, &cursorX, &cursorY);
				glfwGetWindowSize(window, &windowWidth, &windowHeight);

				FrameBuffer fbo(windowWidth, windowHeight);
				fbo.enable();

				sManager->setUniformGLint("idMul", 1);
				scene->renderID();
			
				glReadPixels((int) cursorX, windowHeight - (int) cursorY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
				// We are only checking the blue component, 
				// we don't have 255 or more meshes 
				if (data[2] == '\0'){
					std::cout << "Did not click on a mesh." << std::endl;
				} else {
					std::cout << "Clicked on mesh id: " << (int) data[2] << std::endl;
				}

				fbo.disable();
			}
			break;
		}
	}
}

void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height) {
	glViewport(0, 0, width, height);
	scene->updateWindowDimensions(width, height);
}

int main(int, char**) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	double glfwInitTime = glfwGetTime();

#if defined(OGF_DEBUG) || defined(_DEBUG)
	std::cout << "Running debug build..." << std::endl;

	glfwSetErrorCallback(Debug::glfwErrorCallback);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "OGF Engine program", NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);

    glewExperimental = GL_TRUE;
    glewInit();
	glGetError(); // "Invalid enumerant" after initializing GLEW

#if defined(OGF_DEBUG) || defined(_DEBUG)
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL version " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	if (glDebugMessageCallback) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Debug::openglDebugCallback, nullptr);
		GLuint unusedIds = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
	} else {
		cout << "Warning: glDebugMessageCallback not available" << endl;
	}
#endif
	
	init();

#if defined(OGF_DEBUG) || defined(_DEBUG)
	double deltaTime = glfwGetTime() - glfwInitTime;
	cout << endl << "Initialized in " << deltaTime << " seconds." << endl;
#endif

	while (!glfwWindowShouldClose(window)) {
		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}
