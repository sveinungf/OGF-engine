#version 330 

in vec3 vTexCoord3;

uniform samplerCube cubeTexture;

out vec4 fColor;

void main() {
	fColor = texture(cubeTexture, vTexCoord3);
} 
