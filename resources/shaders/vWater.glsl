#version 330

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;

out vec3 vertexNormal;
out vec2 vertexTexCoord;
out vec4 vertexColor;
out vec3 eyeDir;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
	mat4 normalMatrix = transpose(inverse(worldToView * objectToWorld));
	vertexNormal = (normalMatrix * vec4(normal, 0)).xyz;

	vec3 vertexInViewSpace = (worldToView * objectToWorld * position).xyz;
	eyeDir = -vertexInViewSpace.xyz;
    
	vertexTexCoord = texCoord;

	gl_Position = viewToClip * worldToView * objectToWorld * position;
}
