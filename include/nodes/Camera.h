#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm/glm.hpp>
#pragma warning(pop)
#include "AbstractNode.h"

using namespace glm;


class Camera : public AbstractNode {

public:
	Camera(float fieldOfView, float zNear, float zFar);
	virtual ~Camera() override {}

	const mat4& getWorldToView() const { return worldToView; }
	const mat4& getViewToClip() const { return viewToClip; }
	void setAspectRatio(float aspectRatio);

	void updateWorldToView();

	void doMove(int deltatime);
	void keyDown(unsigned char key);
	void keyUp(unsigned char key);
	void mouseAction(int button, int state, int x, int y);
	void mouseActive(int x, int y);

	void render();

protected:
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;

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
	vec4 forward;
	vec4 up;

	mat4 worldToView;

	//ViewToClip variables
	mat4 viewToClip;
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
