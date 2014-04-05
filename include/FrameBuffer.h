#pragma once

#include <GL/glew.h>


class FrameBuffer {

public:
	explicit FrameBuffer(const int width, const int height);
	~FrameBuffer();
	
	void enable();
	void disable();

	const GLuint getFBO() const { return fbo; }
	const GLuint getTexture() const { return texture; }

	void reshape(const int width, const int height);

private:
	void generate(const int width, const int height);

	GLuint fbo;
	GLuint depth;
	GLuint texture;
};
