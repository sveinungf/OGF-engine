#include "nodes/Camera.h"


Camera::Camera(float fov, float nearZ, float farZ) : AbstractNode(), fieldOfView(fov),
		zNear(nearZ), zFar(farZ), aspectRatio(0.0f), mouseState(MOUSE_OFF),
		prevX(0), prevY(0), startX(0), startY(0) {

	forward = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);

	for (int i = 0; i < 8; ++i) {
		keys[i] = false;
	}
}

void Camera::setAspectRatio(float aspect) {
	aspectRatio = aspect;
	viewToClip = perspective(fieldOfView, aspectRatio, zNear, zFar);
}

void Camera::updateWorldToView() {
	vec4 position = getPositionVec4();
	forward = objectToWorld * forward;
	up = objectToWorld * up;

	forward = normalize(forward);
	up = normalize(up);

	worldToView = lookAt(vec3(position), vec3(position + forward), vec3(up));
}

void Camera::doMove(double deltaTime){
	int forw = (keys[KEY_W] - keys[KEY_S]);
	int strafe = (keys[KEY_D] - keys[KEY_A]);
	int hover = (keys[KEY_SPACE] - keys[KEY_V]);
	float speed = (float) keys[KEY_LSHIFT] * 3 + 1;

	vec4 translate = vec4(strafe, hover, forw, 0.0f) * speed * (float) deltaTime * 10;

	vec3 a = cross(vec3(forward), vec3(up));
	vec4 newPos = forward * translate.z + up * translate.y + vec4(a, 0.0f) * translate.x;
	move(vec3(newPos));
}

void Camera::keyDown(int key){
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
		case GLFW_KEY_LEFT_SHIFT:
			keys[KEY_LSHIFT] = true;
			break;
	}
}

void Camera::keyUp(int key){
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
		case GLFW_KEY_LEFT_SHIFT:
			keys[KEY_LSHIFT] = false;
			break;
	}
}

void Camera::mouseAction(GLFWwindow* window, int button, int state, int x, int y) {
	switch (button){
	case GLFW_MOUSE_BUTTON_LEFT:
		if (state == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			mouseState = MOUSE_ACTIVE;
			prevX = x;
			prevY = y;
			startX = x;
			startY = y;
		} else {
			glfwSetCursorPos(window, startX, startY);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseState = MOUSE_OFF;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (mouseState == MOUSE_ACTIVE) {
			mouseState = MOUSE_ROLL;
		} else {
			glfwSetCursorPos(window, startX, startY);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseState = MOUSE_OFF;
		}
		break;
	}
}

void Camera::mouseActive(GLFWwindow* window, int x, int y) {
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	if (mouseState != MOUSE_OFF) {
		if (x <= 10 || y <= 10 || x >= windowWidth - 10 || y >= windowHeight - 10) {
			prevX = windowWidth / 2;
			prevY = windowHeight / 2;
			glfwSetCursorPos(window, prevX, prevY);
		} else {
			switch (mouseState){
			case MOUSE_ACTIVE:
				rotate((prevY - y) / 4.0f, (prevX - x) / 4.0f, 0.0f);
				break;
			case MOUSE_ROLL:
				rotate(0.0f, 0.0f, (x - prevX) / 4.0f);
				break;
			}

			prevY = y;
			prevX = x;
		}
	}
}

void Camera::render() {
	updateObjectToWorld(nullptr);
	updateWorldToView();

	for (AbstractNode* child : children) {
		child->render(getWorldToView(), getViewToClip(), transformations);
	}
}

void Camera::renderID() {
	updateObjectToWorld(nullptr);
	updateWorldToView();

	for (AbstractNode* child : children) {
		child->renderID(getWorldToView(), getViewToClip(), transformations);
	}
}

void Camera::rotate(float pitch, float yaw, float roll) {
	vec3 a = cross(vec3(forward), vec3(up));
	
	mat4 rotation = glm::rotate(mat4(), pitch, a);
	rotation = glm::rotate(rotation, yaw, vec3(up));
	rotation = glm::rotate(rotation, roll, vec3(forward));

	forward = normalize(rotation * forward);
	up = normalize(rotation * up);
}
