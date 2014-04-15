#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include "Texture.h"


class TextureCubeMap : public Texture {

public:
	explicit TextureCubeMap(const std::vector<std::string>& filenames);

	virtual ~TextureCubeMap() override {}

	virtual void useAsTextureId(const GLuint id) const override;
};
