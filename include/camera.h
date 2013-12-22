#pragma once

#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <gl\GL.h>
#pragma warning(pop)

#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace glm;


class Camera
{
public:
	Camera();
	Camera(vec3 &position, float fov, float zNear, float zFar);
	
	void rotate(float pitch, float yaw, float roll);
	void translate(vec4 trans);
	
	void setViewToClip(float &aspect);
	void setViewToClip(float &aspect , float &fov, float &zNear, float &zFar);

	mat4 getWorldToView() const;
	const mat4& getViewToClip() const;

	inline vec4 getPosition(){return position;};
	void setPosition(glm::vec4 position);
	void setAspectRatio(float aspectRatio);

	// Control methods, dependant on GLUT
	void keyDown(unsigned char key);
	void keyUp(unsigned char key);
	void mouseAction(int button, int state, int x, int y);
	void mouseActive(int x, int y);

	void doMove(int deltatime);

private:
	vec4 position;
	vec4 forward;
	vec4 up;

	//ViewToClip variables
	mat4 viewToClip;
	float fov;
	float zNear;
	float zFar;
	float aspect;

	//Control variables
	enum{ KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_V, KEY_LSHIFT };
	bool keys[8];
	enum{ MOUSE_ACTIVE, MOUSE_ROLL, MOUSE_OFF};
	int mouseState;
	int prevX, prevY;
	int startX, startY;
};

#pragma warning(disable:4505) // unreferenced local function in glut
