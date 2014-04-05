#include <SOIL.h>
#include "Debug.h"
#include "Image.h"
#include "TextureCubeMap.h"

using namespace std;


TextureCubeMap::TextureCubeMap(const vector<string>& filenames) : Texture() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureName);

	for (int i = 0; i < 6; ++i) {
		Image image(filenames[i], Image::RGBA, false);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelData());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (0 == textureName) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void TextureCubeMap::useAsTextureId(const GLuint id) const {
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureName);
}
