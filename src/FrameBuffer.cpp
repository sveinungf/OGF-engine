#include "FrameBuffer.h"
#include "Texture2D.h"

using namespace std;


FrameBuffer::FrameBuffer(const int width, const int height) : fbo(0), depth(0), texture(0) {
	texture = make_shared<Texture2D>(width, height);
	generate(width, height);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &depth);
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
	texture->resize(width, height);

	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
}

void FrameBuffer::generate(const int width, const int height) {
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &depth);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
	// Initialize color texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getTextureName(), 0);
	
	// Initialize depth renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
