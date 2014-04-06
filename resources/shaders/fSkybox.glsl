#version 330 

in vec3 vTexCoord3;

uniform samplerCube cubeTexture;
uniform int id;

out vec4 fColor;

vec3 encodeID(int id);

void main() {
	if (id == 0) {
		fColor = texture(cubeTexture, vTexCoord3);
	} else {
		fColor = vec4(encodeID(id), 1.0f);
	}
} 
