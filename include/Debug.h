#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;


void checkErrorAndStop(const string& errString, bool stop);

string hyphenPaddedMessage(const string& message, int length = 60);

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam);

void glfwErrorCallback(int error, const char* description);
