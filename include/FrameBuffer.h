#pragma once

#include <memory>
#include <GL/glew.h>
#include "Texture2D.h"


class FrameBuffer {

public:
	explicit FrameBuffer(const int width, const int height);
	FrameBuffer(const FrameBuffer&) = delete;
	~FrameBuffer();

	// Copying disallowed since the dtor calls glDelete* functions
	FrameBuffer& operator=(const FrameBuffer&) = delete;

	const GLuint getFBO() const { return fbo; }
	const std::shared_ptr<Texture2D>& getTexture() const { return texture; }
	
	void enable() const;
	void disable() const;

	void reshape(const int width, const int height);

private:
	void generate(const int width, const int height);

	GLuint fbo;
	GLuint depth;
	std::shared_ptr<Texture2D> texture;
};
