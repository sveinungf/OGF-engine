#pragma warning(push, 0)
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#pragma warning(pop)

#include "components/Blending.h"
#include "components/Instancing.h"
#include "components/SimpleDraw.h"
#include "mesh/AssImpMesh.h"
#include "mesh/Cube.h"
#include "mesh/Quad.h"
#include "mesh/Sphere.h"
#include "mesh/Terrain.h"
#include "nodes/AssImpNode.h"
#include "nodes/LightNode.h"
#include "nodes/MeshNode.h"
#include "LightProperties.h"
#include "MaterialProperties.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "TerrainContentData.h"
#include "FrameBuffer.h"
#include "OGFConfig.h"

namespace sveinung {

vec3 cameraStartPosition(0.0f, 60.0f, -10.0f);
int oldTimeSinceStart;

Scene scene;
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
	std::string resourceBase(OGF_RESOURCE_DIR);

	ShaderProgram instancingShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vInstancing.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fInstancing.glsl", Shader::FRAG)
		<< Shader::LINK;
	ShaderProgram waterShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vWater.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fWater.glsl", Shader::FRAG)
		<< Shader::LINK;
	ShaderProgram lightShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vLightShader.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fLightShader.glsl", Shader::FRAG)
		<< Shader::LINK;
	ShaderProgram terrainShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vTerrain.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fTerrain.glsl", Shader::FRAG)
		<< Shader::LINK;
	ShaderProgram treeShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vTree.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fTree.glsl", Shader::FRAG)
		<< Shader::LINK;
	ShaderProgram bumpMapShader = ShaderProgram()
		<< Shader(resourceBase + "/shaders/vBumpMapLightshader.glsl", Shader::VERT)
		<< Shader(resourceBase + "/shaders/fColorID.glsl", Shader::FRAG)
		<< Shader(resourceBase + "/shaders/fBumpMapLightshader.glsl", Shader::FRAG)
		<< Shader::LINK;

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

	Texture2D* grass = new Texture2D(resourceBase + "/textures/grass.bmp");
	Texture2D* sand = new Texture2D(resourceBase + "/textures/sand_diffuse.png");
	Texture2D* greyrock = new Texture2D(resourceBase + "/textures/rock4.png");
	Texture2D* snow = new Texture2D(resourceBase + "/textures/snow.bmp");
	Texture2D* billboardGrass = new Texture2D(resourceBase + "/textures/billboardgrass.png");
	Texture2D* twig = new Texture2D(resourceBase + "/textures/twig.png");
	Texture2D* bark = new Texture2D(resourceBase + "/textures/bark.png");
	Texture2D* rockNormalMap = new Texture2D(resourceBase + "/textures/S1Normal.jpg");
	Texture2D* rockDiffus = new Texture2D(resourceBase + "/textures/S3Diffus.jpg");

	light = new LightNode(sManager, &LightProperties::SUNLIGHT);

	grassInstancing = new Instancing(contentData.getGrassPositions(), contentData.getGrassNormals());
	grassNode = new MeshNode(instancingShader, grassMesh);
	grassNode->addComponent(grassInstancing);
	grassNode->addComponent(blending);
	grassNode->addTexture(billboardGrass);
	grassNode->move(0.0f, 0.5f, 0.0f);
	
	waterNode = new MeshNode(waterShader, waterMesh);
	waterNode->addComponent(simpleDraw);
	waterNode->addTexture(new Texture2D(resourceBase + "/textures/water.jpg"));
	waterNode->rotateAroundSelfX(90.0f);
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
	terrain->addComponent(simpleDraw);
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

	scene.init();
	scene.setCameraPosition(cameraStartPosition);
	scene.setRootNode(terrain);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	std::cout << std::endl << "Ready!" << std::endl << std::endl;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (renderID) {
		sManager->setUniformGLint("idMul", 3425160);
		scene.renderID();
	} else {
		scene.render();
	}
	glutSwapBuffers();
}

//----------------------------------------------------------------------------

//Reshape window without losing aspect ratio
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	float asp = (float) width/height;
	scene.getCamera()->setAspectRatio(asp);
}

void keySpecial(int key, int /*x*/, int /*y*/) {
	scene.getCamera()->keyDown((unsigned char)key);
}

void keySpecialUp(int key, int /*x*/, int /*y*/) {
	scene.getCamera()->keyUp((unsigned char)key);
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
	scene.getCamera()->keyDown(key);
    switch (key) {
		case 'o':
		case 'O':
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // show wireframe
			break;

		case 'i':
		case 'I':
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // back to default
			break;

		case 'p':
		case 'P':
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // show points
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

        case 033: // Escape Key
            exit(EXIT_SUCCESS);
            break;

    }
}

void keyboardUp(unsigned char key, int /*x*/, int /*y*/) {
	scene.getCamera()->keyUp(key);
}

void mouse( int button, int state, int x, int y ) {
	scene.getCamera()->mouseAction(button, state, x, y);
	if (state == GLUT_DOWN){
		switch (button){
		case GLUT_MIDDLE_BUTTON:
			FrameBuffer fbo = FrameBuffer(
					glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

			fbo.enable();
				sManager->setUniformGLint("idMul", 1);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				scene.renderID();
				unsigned char data[4] = { 0 };
				glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 
					1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
				// We are only checking the blue component, 
				// we don't have 255 or more meshes 
				if (data[2] == '\0'){
					std::cout << "Did not click on a mesh." << std::endl;
				} else{
					std::cout << "Clicked on mesh id: "
						<< (int)data[2] << std::endl;
				}
			fbo.disable();
			break;
		}
	}
}

void activeMouse(int x, int y){
	scene.getCamera()->mouseActive(x, y);
}

void idle(void) {
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	scene.getCamera()->doMove(deltaTime);
	sunSphere->rotateAroundOriginZ(0.01f * deltaTime);
	glutPostRedisplay();
}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("OGF Engine program");

    glewExperimental = GL_TRUE;

    glewInit();
	checkErrorAndStop("after glewinit", false);

	sveinung::init();
	sveinung::oldTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	glutDisplayFunc(sveinung::display);
    glutReshapeFunc(sveinung::reshape);
    glutKeyboardFunc(sveinung::keyboard);
	glutKeyboardUpFunc(sveinung::keyboardUp);
    glutMouseFunc( sveinung::mouse );
	glutMotionFunc(sveinung::activeMouse);
	glutSpecialFunc(sveinung::keySpecial);
	glutSpecialUpFunc(sveinung::keySpecialUp);
	glutIdleFunc(sveinung::idle);

    glutMainLoop();
    return 0;
}

#pragma warning(disable:4505) // unreferenced local function in glut
