#version 330

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;

out vec3 pos_eye;
out vec3 n_eye;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
	pos_eye = vec3(worldToView * objectToWorld * position);
	n_eye = vec3(worldToView * objectToWorld * vec4(normal, 0.0f));
	gl_Position = viewToClip * worldToView * objectToWorld * position;
}
