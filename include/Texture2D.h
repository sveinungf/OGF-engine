#pragma once

#include <string>
#include <GL/glew.h>
#include "Image.h"
#include "Texture.h"


class Texture2D : public Texture {

public:
    explicit Texture2D(const std::string& filename, bool generateMipMaps = true);

    virtual void useAsTextureId(const GLuint id) const override;
	const Image& getImage() const { return image; }

private:
    Image image;
};
