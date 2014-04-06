#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Debug {

public:
	// OpenGL
	static void checkErrorAndStop(const std::string& errString, bool stop);
	static void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam);

	// GLFW
	static void glfwErrorCallback(int error, const char* description);

private:
	static std::string hyphenPaddedMessage(const std::string& message, int length = 60);
};
