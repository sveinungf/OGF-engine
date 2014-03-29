#version 330 

layout (location = 1) in vec4 position;

out vec4 vPosition;
out vec3 vTexCoord3;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
    vPosition = position;
	vec4 posInWorldCoords = objectToWorld * position;
	vTexCoord3 = posInWorldCoords.xyz;
    gl_Position = viewToClip * worldToView * posInWorldCoords;
}
