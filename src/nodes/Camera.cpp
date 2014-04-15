#include "nodes/Camera.h"

using namespace glm;


Camera::Camera(const float fov, const float nearZ, const float farZ) : AbstractNode(), windowWidth(0), windowHeight(0), forward(0.0f, 0.0f, -1.0f, 0.0f), up(0.0f, 1.0f, 0.0f, 0.0f), fieldOfView(fov),
		zNear(nearZ), zFar(farZ), mouseState(MOUSE_OFF), prevX(0), prevY(0), startX(0), startY(0) {

	for (int i = 0; i < MAX_KEYS; ++i) {
		keys[i] = false;
	}
}

void Camera::updateWindowDimensions(const int width, const int height) {
	windowWidth = width;
	windowHeight = height;
	viewToClip = perspective(fieldOfView, (float) width / height, zNear, zFar);
}

void Camera::updateWorldToView() {
	vec4 position = getPositionVec4();
	forward = objectToWorld * forward;
	up = objectToWorld * up;

	forward = normalize(forward);
	up = normalize(up);

	worldToView = lookAt(vec3(position), vec3(position + forward), vec3(up));
	worldToViewNoTranslation = lookAt(vec3(), vec3(forward), vec3(up));
}

void Camera::doMove(const double deltaTime){
	int forw = (keys[KEY_W] - keys[KEY_S]);
	int strafe = (keys[KEY_D] - keys[KEY_A]);
	int hover = (keys[KEY_SPACE] - keys[KEY_V]);
	float speed = (float) keys[KEY_LSHIFT] * 3 + 1;

	vec4 translate = vec4(strafe, hover, forw, 0.0f) * speed * (float) deltaTime * 10;

	vec3 a = cross(vec3(forward), vec3(up));
	vec4 newPos = forward * translate.z + up * translate.y + vec4(a, 0.0f) * translate.x;
	move(vec3(newPos));
}

void Camera::keyDown(const int key){
	switch (key) {
	case 'k':
	case 'K':
		std::cout << "CAMERA POS: " << glm::to_string(getPositionVec4()) << std::endl;
		break;
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

void Camera::keyUp(const int key){
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

void Camera::mouseAction(GLFWwindow* const window, const int button, const int state) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		if (state == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			mouseState = MOUSE_ACTIVE;
			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseState = MOUSE_OFF;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (state == GLFW_PRESS) {
			if (mouseState == MOUSE_ACTIVE) {
				mouseState = MOUSE_ROLL;
			}
		} else {
			if (mouseState == MOUSE_ROLL) {
				mouseState = MOUSE_ACTIVE;
			}
		}
		break;
	}
}

void Camera::mouseActive(GLFWwindow* const window, const int x, const int y) {
	if (mouseState != MOUSE_OFF) {
		int middleX = windowWidth / 2;
		int middleY = windowHeight / 2;

		switch (mouseState) {
		case MOUSE_ACTIVE:
			rotate((middleY - y) / 4.0f, (middleX - x) / 4.0f, 0.0f);
			break;
		case MOUSE_ROLL:
			rotate(0.0f, 0.0f, (x - middleX) / 4.0f);
			break;
		}

		glfwSetCursorPos(window, middleX, middleY);
	}
}

void Camera::render() {
	updateObjectToWorld(nullptr);
	updateWorldToView();

	for (const auto& child : children) {
		child->render(getWorldToView(), getViewToClip(), &transformations);
	}
}

void Camera::renderID() {
	updateObjectToWorld(nullptr);
	updateWorldToView();

	for (const auto& child : children) {
		child->renderID(getWorldToView(), getViewToClip(), &transformations);
	}
}

void Camera::rotate(const float pitch, const float yaw, const float roll) {
	vec3 a = cross(vec3(forward), vec3(up));

	mat4 rotation = glm::rotate(mat4(), pitch, a);
	rotation = glm::rotate(rotation, yaw, vec3(up));
	rotation = glm::rotate(rotation, roll, vec3(forward));

	forward = normalize(rotation * forward);
	up = normalize(rotation * up);
}
