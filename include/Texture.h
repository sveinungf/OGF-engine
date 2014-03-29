#pragma once

#include <GL/glew.h>


class Texture {

public:
	virtual void useAsTextureId(const GLuint id) const = 0;

protected:
	Texture();

	GLuint textureName;
};
