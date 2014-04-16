#version 330

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 4) in vec2 texCoord;

out vec3 pos_eye;
out vec3 n_eye;
out vec2 vertexTexCoord;
out vec4 texCoordProject;


out vec3 eyeDir;
out vec3 vNormal;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
	mat4 objectToView = worldToView * objectToWorld;

	mat4 normalMatrix = transpose(inverse(objectToView));
	vNormal = (normalMatrix * vec4(normal, 0.0f)).xyz;
	eyeDir = -(objectToView * position).xyz;
	
	
	vertexTexCoord = texCoord;
	pos_eye = vec3(worldToView * objectToWorld * position);
	n_eye = vec3(worldToView * objectToWorld * vec4(normal, 0.0f));
	texCoordProject = viewToClip * worldToView * objectToWorld * position;
	texCoordProject.xy = 0.5 * texCoordProject.xy + 0.5 * texCoordProject.w;
	gl_Position = viewToClip * worldToView * objectToWorld * position;
}
