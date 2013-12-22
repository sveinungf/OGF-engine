#version 330 

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;

//Passing everything to the fragment shader
out vec4 vPosition;
out vec3 vNormal;
out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
    vPosition = position;
    vNormal = normal;
    vColor = color;
	vTexCoord = texCoord;

	//mat4 t = (worldToView * objectToWorld * instanceTransformation);


    gl_Position = viewToClip * worldToView * objectToWorld * position;
} 