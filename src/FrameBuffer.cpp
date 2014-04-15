#include "FrameBuffer.h"


FrameBuffer::FrameBuffer(const int width, const int height) : fbo(0), depth(0), texture(0) {
	generate(width, height);
}

FrameBuffer::~FrameBuffer() {
	cleanup();
}

void FrameBuffer::enable() const {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	static const GLfloat depthValue = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &depthValue);
}

void FrameBuffer::disable() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::reshape(const int width, const int height) {
	cleanup();
	generate(width, height);
}

void FrameBuffer::cleanup() {
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);
	glDeleteRenderbuffers(1, &depth);
}

void FrameBuffer::generate(const int width, const int height) {
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &texture);
	glGenRenderbuffers(1, &depth);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
	// Initialize color texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	
	// Initialize depth renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
