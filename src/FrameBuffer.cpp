#include "FrameBuffer.h"


FrameBuffer::FrameBuffer() {
	generate(1024, 1024);
}

FrameBuffer::FrameBuffer(int width, int height) {
	generate(width, height);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &depth);
}

void FrameBuffer::enable() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	static const GLfloat green[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, green);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void FrameBuffer::disable() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::reshape(int width, int height) {
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &depth);
	generate(width, height);
}

void FrameBuffer::generate(int width, int height) {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGBA8, width, height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &depth);
	glBindTexture(GL_TEXTURE_2D, depth);
	glTexStorage2D(GL_TEXTURE_2D, 9, GL_DEPTH_COMPONENT32F, width, height);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

	static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, draw_buffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
