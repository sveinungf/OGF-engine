#pragma once

#include <GL/glew.h>


class FrameBuffer {

public:
	FrameBuffer();
	FrameBuffer(int width, int height);
	~FrameBuffer();
	
	void enable();
	void disable();

	const GLuint& getFBO() { return fbo; }
	const GLuint& getTexture() const { return texture; }

	void reshape(int width, int height);

private:
	void generate(int width, int height);

	GLuint fbo;
	GLuint texture;
	GLuint depth;
};
