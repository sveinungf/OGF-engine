#include "camera.h"
#include <GL\freeglut.h>


using namespace glm;

mat4 rotateAroundAxis(vec4 axis, float angle)
{
	float a = angle * pi<float>()/180.0f;
	float s = sin(a);
	float c = cos(a);
	
	return mat4(
		c+(1-c)* pow(axis.x,2), (1-c)*axis.y*axis.x - s*axis.z, (1-c)*axis.z*axis.x+s*axis.y, 0,
		(1-c)*axis.x *axis.y + s*axis.z, c+(1-c)*pow(axis.y,2), (1-c)*axis.z*axis.y-s*axis.x, 0,
		(1-c)*axis.x *axis.z - s*axis.y, (1-c)*axis.y*axis.z+s*axis.x, c+(1-c)*pow(axis.z,2), 0,
		0,0,0,1
		);
}

Camera::Camera() : mouseState(MOUSE_OFF)
{
	position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	forward = vec4(0,0,1,0);
	up = vec4(0,1,0,0);

	fov = 75.0f;
	zNear = 0.01f;
	zFar = 435.0f;

	for (int i = 0; i < 8; i++){
		keys[i] = false;
	}
}

Camera::Camera(vec3 &position, float fov, float zNear, float zFar) : mouseState(MOUSE_OFF)
{
	this->position = vec4(position,1.0f);
	forward = vec4(0,0,1,0);
	up = vec4(0,1,0,0);

	this->fov = fov;
	this->zNear =zNear;
	this->zFar = zFar;
	for (int i = 0; i < 8; i++){
		keys[i] = false;
	}
}

void Camera::setPosition(glm::vec4 position){
	this->position = position;
}

void Camera::rotate(float pitch, float yaw, float roll)
{
	vec3 a = cross(vec3(forward.x,forward.y,forward.z),vec3(up.x,up.y,up.z));
	mat4 rotation = rotateAroundAxis( vec4(a.x,a.y,a.z,0), pitch);
	rotation *= rotateAroundAxis(up,yaw);
	rotation *= rotateAroundAxis(forward,roll);
	forward = normalize(rotation * forward);
	up = normalize(rotation * up);
}

void Camera::translate(vec4 trans)
{
	
	vec3 a = cross(
		vec3(forward.x,forward.y,forward.z),
		vec3(up.x,up.y,up.z)
	);
	position += forward*trans.z + up*trans.y + vec4(a.x,a.y,a.z,0)*trans.x;
	position.w = 1.0f;
}

mat4 Camera::getWorldToView() const
{
	vec4 a = position + forward;
	return lookAt(vec3(position.x,position.y,position.z),
		vec3(a.x,a.y,a.z), vec3(up.x,up.y,up.z));
}

const mat4& Camera::getViewToClip() const {
	return viewToClip;
}

void Camera::setViewToClip(float &aspect){
	viewToClip = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::setAspectRatio(float aspectRatio){
	aspect=aspectRatio;
	viewToClip = glm::perspective(fov, aspect, zNear, zFar);
};

void Camera::doMove(int deltatime){
	int forward = (keys[KEY_W] - keys[KEY_S]);
	int strafe = (keys[KEY_D] - keys[KEY_A]);
	int hover = (keys[KEY_SPACE] - keys[KEY_V]);
	float speed = (float) keys[KEY_LSHIFT] * 3 + 1;

	this->translate(vec4(strafe, hover, forward, 0)  * speed * (float)deltatime / 100.0f);
}

// Control methods, dependant on GLUT
void Camera::keyDown(unsigned char key){
	switch (key) {

		case 'w':
		case 'W':
			keys[KEY_W] = true;
			break;
		case 'a':
		case 'A':
			keys[KEY_A] = true;
			break;
		case 's':
		case 'S':
			keys[KEY_S] = true;
			break;
		case 'd':
		case 'D':
			keys[KEY_D] = true;
			break;
		case ' ':
			keys[KEY_SPACE] = true;
			break;
		case 'v':
		case 'V':
			keys[KEY_V] = true;
			break;
		case GLUT_KEY_SHIFT_L:
			keys[KEY_LSHIFT] = true;
			break;
	}
}

void Camera::keyUp(unsigned char key){
	switch (key) {
		case 'w':
		case 'W':
			keys[KEY_W] = false;
			break;
		case 'a':
		case 'A':
			keys[KEY_A] = false;
			break;
		case 's':
		case 'S':
			keys[KEY_S] = false;
			break;
		case 'd':
		case 'D':
			keys[KEY_D] = false;
			break;
		case ' ':
			keys[KEY_SPACE] = false;
			break;
		case 'v':
		case 'V':
			keys[KEY_V] = false;
			break;
		case GLUT_KEY_SHIFT_L:
			keys[KEY_LSHIFT] = false;
			break;
	}
}

void Camera::mouseAction(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			mouseState = MOUSE_ACTIVE;
			prevX = x;
			prevY = y;
			startX = x;
			startY = y;
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else{
			mouseState = 0;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutWarpPointer(startX, startY);
			mouseState = MOUSE_OFF;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (mouseState == MOUSE_ACTIVE){
			mouseState = MOUSE_ROLL;
		}
		else{
			mouseState = MOUSE_OFF;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutWarpPointer(startX, startY);
		}
		break;
	}
}

void Camera::mouseActive(int x, int y){
	if (mouseState != MOUSE_OFF){
		int wWidth = glutGet(GLUT_WINDOW_WIDTH);
		int wHeight = glutGet(GLUT_WINDOW_HEIGHT);
		if (x <= 10 || y <= 10 || x >= wWidth - 10 || y >= wHeight - 10){
			glutWarpPointer(wWidth / 2, wHeight / 2);
			prevX = wWidth / 2;
			prevY = wHeight / 2;
		}
		else{

			switch (mouseState){
			case MOUSE_ACTIVE:
				rotate((y - prevY) / 4.0f, (x - prevX) / 4.0f, 0);
				break;
			case MOUSE_ROLL:
				rotate(0, 0, (x - prevX) / 4.0f);
				break;
			}
			prevY = y;
			prevX = x;
		}
	}
}
