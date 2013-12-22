#version 330

layout (location = 1) in vec4 position;

uniform mat4 objectToWorld;
uniform mat4 worldToView; 
uniform mat4 viewToClip;

void main()
{
	gl_Position = viewToClip * worldToView * objectToWorld * position;
}