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

void Camera::doMove(int deltatime){
	int forw = (keys[KEY_W] - keys[KEY_S]);
	int strafe = (keys[KEY_D] - keys[KEY_A]);
	int hover = (keys[KEY_SPACE] - keys[KEY_V]);
	float speed = (float) keys[KEY_LSHIFT] * 3 + 1;

	vec4 translate = vec4(strafe, hover, forw, 0.0f) * speed * (float) deltatime / 100.0f;

	vec3 a = cross(vec3(forward), vec3(up));
	vec4 newPos = forward * translate.z + up * translate.y + vec4(a, 0.0f) * translate.x;
	move(vec3(newPos));
}

void Camera::keyDown(unsigned char key){
	switch (key) {
		case 'k':
			std::cout << glm::to_string(getPositionVec4()) << std::endl << std::endl;
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
		if (state == GLUT_DOWN) {
			mouseState = MOUSE_ACTIVE;
			prevX = x;
			prevY = y;
			startX = x;
			startY = y;
			glutSetCursor(GLUT_CURSOR_NONE);
		} else {
			mouseState = 0;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutWarpPointer(startX, startY);
			mouseState = MOUSE_OFF;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (mouseState == MOUSE_ACTIVE) {
			mouseState = MOUSE_ROLL;
		} else {
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

		if (x <= 10 || y <= 10 || x >= wWidth - 10 || y >= wHeight - 10) {
			glutWarpPointer(wWidth / 2, wHeight / 2);
			prevX = wWidth / 2;
			prevY = wHeight / 2;
		} else {
			switch (mouseState){
			case MOUSE_ACTIVE:
				rotate((prevY - y) / 4.0f, (prevX - x) / 4.0f, 0);
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

void Camera::render() {
	updateObjectToWorld(nullptr);
	updateWorldToView();

	//transformations[ROTATION_SELF] = mat4(1.0f);

	for (AbstractNode* child : children) {
		child->render(getWorldToView(), getViewToClip(), transformations);
	}
}

void Camera::renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	updateObjectToWorld(parentTransformations);
	updateWorldToView();
	
	transformations[ROTATION_SELF] = mat4(1.0f);
}

void Camera::renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	renderSelf(worldToView, viewToClip, parentTransformations);
}

void Camera::rotate(float pitch, float yaw, float roll) {
	vec3 a = cross(vec3(forward), vec3(up));
	
	mat4 rotation = glm::rotate(mat4(), pitch, a);
	rotation = glm::rotate(rotation, yaw, vec3(up));
	rotation = glm::rotate(rotation, roll, vec3(forward));

	forward = normalize(rotation * forward);
	up = normalize(rotation * up);
}
