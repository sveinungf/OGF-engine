#version 330 

in vec4 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D texture0; 

out vec4 fColor;  //Color out for this fragment

void main() {
	fColor = texture2D(texture0, vTexCoord);
} 
