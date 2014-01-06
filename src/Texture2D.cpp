#include "Texture2D.h"
#include <iostream>

Texture2D::Texture2D(const std::string& filename, bool generateMipMaps) {
	std::cout << "Loading texture: " << filename << std::endl;
	image = new Image(filename, Image::RGBA);

    // Lager lokasjon for 1 tekstur (denne) i GPU minne
    glGenTextures(1, &textureName);

    // M� binde teksturen for � sette parametre
    glBindTexture(GL_TEXTURE_2D, textureName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (generateMipMaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // to eliminate *white edge* effect
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

Texture2D::~Texture2D() {
	delete image;
}

void Texture2D::useAsTextureId(const GLuint& id) const {
    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, textureName);
}

Image* Texture2D::getImage(){
	return image;
}
