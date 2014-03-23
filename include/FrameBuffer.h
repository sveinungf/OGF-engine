#pragma once

#include <GL/glew.h>


class FrameBuffer {

public:
	FrameBuffer();
	explicit FrameBuffer(int width, int height);
	~FrameBuffer();
	
	void enable();
	void disable();

	const GLuint getFBO() { return fbo; }
	const GLuint getTexture() const { return texture; }

	void reshape(int width, int height);

private:
	void generate(int width, int height);

	GLuint fbo;
	GLuint depth;
	GLuint texture;
};
