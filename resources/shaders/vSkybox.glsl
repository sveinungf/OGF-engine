#version 330 

layout (location = 1) in vec4 position;
layout (location = 4) in vec2 texCoord;

out vec4 vPosition;
out vec2 vTexCoord2;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
    vPosition = position;
	vTexCoord2 = texCoord;
	
    gl_Position = viewToClip * worldToView * objectToWorld * position;
}
