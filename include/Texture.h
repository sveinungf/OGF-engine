#pragma once

#include <GL/glew.h>


class Texture {

public:
	// Virtual constructor idiom
	virtual Texture* clone() const = 0;

	virtual ~Texture() {}

	virtual void useAsTextureId(const GLuint id) const = 0;

protected:
	Texture();

	GLuint textureName;
};
