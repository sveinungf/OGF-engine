#version 330 

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;
layout (location = 7) in vec3 instancePosition;
layout (location = 8) in vec3 instanceNormal;

//Passing everything to the fragment shader
out vec4 vPosition;
out vec3 vNormal;
out vec4 vColor;
out vec2 vTexCoord;
out vec3 eyeDir;

uniform mat4 objectToWorld;
uniform mat4 worldToView;
uniform mat4 viewToClip;

void main() {
    vPosition = position;
    vColor = color;
	vTexCoord = texCoord;

	mat4 objectToView = worldToView * objectToWorld;

	mat4 normalMatrix = transpose(inverse(objectToView));
	vNormal = (normalMatrix * vec4(instanceNormal, 0.0f)).xyz;
	eyeDir = -(objectToView * vec4(instancePosition, 1.0f)).xyz;

	mat4 instanceTransformation = mat4(1.0f);
	instanceTransformation[3][0] = instancePosition.x;
	instanceTransformation[3][1] = instancePosition.y;
	instanceTransformation[3][2] = instancePosition.z;

	mat4 objectToBillboardView = objectToView * instanceTransformation;
	objectToBillboardView[0][0] = objectToBillboardView[1][1]; // Keep eventual symmetrical scale
	objectToBillboardView[0][1] = 0.0f;
	objectToBillboardView[0][2] = 0.0f;

	objectToBillboardView[2][0] = 0.0f;
	objectToBillboardView[2][1] = 0.0f;
	objectToBillboardView[2][2] = objectToBillboardView[1][1];

    gl_Position = viewToClip * objectToBillboardView * position;
} 
