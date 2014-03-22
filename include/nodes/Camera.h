#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glmhppnowarnings.h>
#include "AbstractNode.h"


class Camera : public AbstractNode {

public:
	explicit Camera(float fieldOfView, float zNear, float zFar);
	virtual ~Camera() override {}

	const glm::mat4& getWorldToView() const { return worldToView; }
	const glm::mat4& getViewToClip() const { return viewToClip; }
	void setAspectRatio(float aspectRatio);

	void updateWorldToView();

	void doMove(double deltaTime);
	void keyDown(int key);
	void keyUp(int key);
	void mouseAction(GLFWwindow* window, int button, int state, int x, int y);
	void mouseActive(GLFWwindow* window, int x, int y);

	void render();
	void renderID();

protected:
	virtual void renderSelf(const glm::mat4&, const glm::mat4&) override {}
	virtual void renderIDSelf(const glm::mat4&, const glm::mat4&) override {}

private:
	enum CameraKeys {
		KEY_W = 0,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_SPACE,
		KEY_V,
		KEY_LSHIFT
	};

	enum MouseStates {
		MOUSE_ACTIVE = 0,
		MOUSE_ROLL,
		MOUSE_OFF
	};

	//vec4 position;
	glm::vec4 forward;
	glm::vec4 up;

	glm::mat4 worldToView;

	//ViewToClip variables
	glm::mat4 viewToClip;
	float fieldOfView;
	float zNear;
	float zFar;
	float aspectRatio;

	//Control variables
	bool keys[8];
	int mouseState;
	int prevX;
	int prevY;
	int startX;
	int startY;

	void rotate(float pitch, float yaw, float roll);
};

#endif /* CAMERA_H_ */
