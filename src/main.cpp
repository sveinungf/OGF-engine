#include <iostream>
#include <memory>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glmhppnowarnings.h>
#include <glm/gtx/transform.hpp>

#include "components/Blending.h"
#include "components/Instancing.h"
#include "components/SimpleDraw.h"
#include "components/IBODraw.h"
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
AssImpNode* tree;
AssImpNode* rock;
MeshNode* grassNode;
MeshNode* waterNode;
MeshNode* sunSphere;
MeshNode* terrain;
LightNode* light;
ShaderProgram* instancingShader;
Instancing* grassInstancing;
Instancing* treeInstancing;
ShaderManager* sManager;

bool renderID = false;

void init() {
	oldTimeSinceStart = glfwGetTime();
	previousTime = oldTimeSinceStart;

	std::string resourceBase(OGF_RESOURCE_DIR);

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
	sManager->add(instancingShader);
	sManager->add(waterShader);
	sManager->add(lightShader);
	sManager->add(terrainShader);
	sManager->add(treeShader);
	sManager->add(bumpMapShader);

	Terrain* terrainMesh = new Terrain(resourceBase + "/heightmaps/heightmap.tga");
	Quad* grassMesh = new Quad();
	Quad* waterMesh = new Quad();
	Sphere* sphereMesh = new Sphere();

	TerrainContentData contentData = terrainMesh->getContentData();
	terrainShader.setTerrainContentData(contentData);

	std::cout << "Grass instances: " << contentData.getGrassPositions().size() << std::endl;
	std::cout << "Tree instances: " << contentData.getTreePositions().size() << std::endl;

	Blending* blending = new Blending();
	SimpleDraw* simpleDraw = new SimpleDraw();
	IBODraw* ibodraw = new IBODraw();

	//Texture* grass = new Texture2D(resourceBase + "/textures/grass.bmp");
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
	skyboxImages.push_back(resourceBase + "/skyboxes/right.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/left.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/top.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/bottom.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/front.bmp");
	skyboxImages.push_back(resourceBase + "/skyboxes/back.bmp");
	shared_ptr<TextureCubeMap> skyboxTexture(make_shared<TextureCubeMap>(skyboxImages));

	light = new LightNode(sManager, &LightProperties::SUNLIGHT);

	grassInstancing = new Instancing(contentData.getGrassPositions(), contentData.getGrassNormals());
	grassNode = new MeshNode(instancingShader, grassMesh);
	grassNode->addComponent(grassInstancing);
	grassNode->addComponent(blending);
	grassNode->addTexture(billboardGrass);
	grassNode->move(0.0f, 0.5f, 0.0f);
	
	waterNode = new MeshNode(waterShader, waterMesh);
	waterNode->addComponent(ibodraw);
	waterNode->addComponent(blending);
	waterNode->addTexture(skyboxTexture);
	waterNode->rotateAroundSelfX(-90.0f);
	waterNode->scale((GLfloat) terrainMesh->getWidth(), (GLfloat) terrainMesh->getLength(), 1.0f);

	sunSphere = new MeshNode(lightShader, sphereMesh);
	sunSphere->addComponent(simpleDraw);
	sunSphere->move(200.0f, 0.0f, 0.0f);
	sunSphere->add(light);
	
	treeInstancing = new Instancing(contentData.getTreePositions());
	tree = new AssImpNode(treeShader, resourceBase + "/tree.3ds");
	tree->addComponent(treeInstancing);
	tree->addComponent(blending);
	tree->addTexture(twig, 0);
	tree->addTexture(bark, 1);
	tree->addTexture(bark, 2);
	tree->addTexture(bark, 3);
	
	terrain = new MeshNode(terrainShader, terrainMesh);
	terrain->addComponent(ibodraw);
	terrain->addTexture(sand);
	terrain->addTexture(grass);
	terrain->addTexture(greyrock);
	terrain->addTexture(snow);
	terrain->add(sunSphere);
	terrain->add(grassNode);
	terrain->add(waterNode);
	terrain->add(tree);

	rock = new AssImpNode(bumpMapShader, resourceBase + "/Stone_Forest_1.obj");
	rock->addComponent(simpleDraw);
	rock->move(0.0f, 0.45f, 0.0f);
	terrain->add(rock);
	rock->scale(0.02f, 0.02f, 0.02f);
	rock->move(terrainMesh->getPointAt(50, 50));
	rock->addTexture(rockNormalMap);
	rock->addTexture(rockDiffus);

	Skybox skybox(skyboxShader, skyboxTexture);
	scene = new Scene(skybox);
	scene->getCamera().updateWindowDimensions(width, height);
	scene->setCameraPosition(cameraStartPosition);
	scene->setRootNode(terrain);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	std::cout << std::endl << "Ready!" << std::endl << std::endl;
}

void display(void) {
	double timeSinceStart = glfwGetTime();
	double deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	scene->getCamera().doMove(deltaTime);
	sunSphere->rotateAroundOriginZ(5 * (float) deltaTime);

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
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	scene->getCamera().updateWindowDimensions(width, height);
}

int main(int, char**) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

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

	cout << "OpenGL version " << glGetString(GL_VERSION) << endl;

#if defined(OGF_DEBUG) || defined(_DEBUG)
	if (glDebugMessageCallback) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Debug::openglDebugCallback, nullptr);
		GLuint unusedIds = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
	} else {
		cout << "glDebugMessageCallback not available" << endl;
	}
#endif
	
	init();

	while (!glfwWindowShouldClose(window)) {
		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}
