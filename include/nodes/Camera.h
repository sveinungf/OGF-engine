#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glmhppnowarnings.h>
#include "AbstractNode.h"


class Camera : public AbstractNode {

public:
	explicit Camera(const float fieldOfView, const float zNear, const float zFar);

	// Virtual constructor idiom
	virtual Camera* clone() const override { return new Camera(*this); }

	virtual ~Camera() override {}

	const glm::mat4& getWorldToView() const { return worldToView; }
	const glm::mat4& getWorldToViewNoTranslation() const { return worldToViewNoTranslation; }
	const glm::mat4& getViewToClip() const { return viewToClip; }
	
	void updateWindowDimensions(const int width, const int height);

	void updateWorldToView();

	void doMove(const double deltaTime);
	void keyDown(const int key);
	void keyUp(const int key);
	void mouseAction(GLFWwindow* const window, const int button, const int state);
	void mouseActive(GLFWwindow* const window, const int x, const int y);

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
		KEY_LSHIFT,
		//--------
		MAX_KEYS
	};

	enum MouseStates {
		MOUSE_ACTIVE = 0,
		MOUSE_ROLL,
		MOUSE_OFF
	};

	int windowWidth, windowHeight;

	glm::vec4 forward;
	glm::vec4 up;

	glm::mat4 worldToView;
	glm::mat4 worldToViewNoTranslation;

	//ViewToClip variables
	glm::mat4 viewToClip;
	float fieldOfView;
	float zNear;
	float zFar;

	//Control variables
	bool keys[MAX_KEYS];
	int mouseState;
	int prevX;
	int prevY;
	int startX;
	int startY;

	void rotate(const float pitch, const float yaw, const float roll);
};

#endif /* CAMERA_H_ */
