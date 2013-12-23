#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>


class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(int width, int height);
	~FrameBuffer();
	
	void enable();
	void disable();

	GLuint getTexture();
	GLuint getFBO(){ return fbo; }

	void reshape(int width, int height);
private:
	void generate(int width, int height);

	GLuint fbo;
	GLuint texture;
	GLuint depth;
};

#pragma warning(disable:4505) // unreferenced local function in glut
