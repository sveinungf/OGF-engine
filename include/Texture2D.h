#pragma once

#include <string>
#include <GL/glew.h>
#include "Image.h"
#include "Texture.h"


class Texture2D : public Texture {

public:
	explicit Texture2D(const int width, const int height);
    explicit Texture2D(const std::string& filename, bool generateMipMaps = true);
	virtual ~Texture2D() override {}

	void resize(const int width, const int height);

	virtual int getType() const override { return GL_TEXTURE_2D; }
    virtual void useAsTextureId(const GLuint id) const override;

private:
	bool fromImage;
};
