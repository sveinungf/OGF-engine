#include <SOIL.h>
#include "TextureCubeMap.h"

using namespace std;


TextureCubeMap::TextureCubeMap(const vector<string>& filenames) : Texture() {
	textureName = SOIL_load_OGL_cubemap(filenames[0].c_str(), filenames[1].c_str(), filenames[2].c_str(), filenames[3].c_str(), filenames[4].c_str(), filenames[5].c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

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
