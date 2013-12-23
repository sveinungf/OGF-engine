#pragma once

#include <string>
#include <GL/glew.h>
#include "Image.h"


class Texture2D {

public:
    Texture2D(const std::string& filename, bool generateMipMaps = true);
	Texture2D(const GLuint& premade);
    ~Texture2D();

    void useAsTextureId(const GLuint& id) const;
	Image* getImage();

private:
    Image* image;
    GLuint textureName;
};
