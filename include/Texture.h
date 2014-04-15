#pragma once

#include <GL/glew.h>


class Texture {

public:
	// Copying disallowed since the dtor calls glDelete* functions
	Texture(const Texture&) = delete;
	virtual ~Texture();

	Texture& operator=(const Texture&) = delete;

	const GLuint getTextureName() const { return textureName; }

	virtual void useAsTextureId(const GLuint id) const = 0;

protected:
	Texture();

	GLuint textureName;
};
