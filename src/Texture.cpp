#include "Texture.h"


Texture::Texture() {
	glGenTextures(1, &textureName);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureName);
}
