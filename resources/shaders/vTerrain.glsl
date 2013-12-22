#version 330

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;

uniform mat4 objectToWorld; //a.k.a model
uniform mat4 worldToView;   //a.k.a view
uniform mat4 viewToClip;    //a.k.a projection

out float vHeight;

out vec3 vertexNormal;
out vec2 vertexTexCoord;
out vec4 vertexColor;   //Ikkje i bruk, men tatt med for debugging
out vec3 eyeDir;        //vektoren fraa camera (auget) til verteksen
out vec3 vertexOriginalNormal;  //brukes til forskjellige textures i fragmentshader basert på "slope"

void main() {
    // bring normal into view Space -> Important otherwise the normal will be incorrect in relation to ModelView space
	mat4 normalMatrix = transpose(inverse(worldToView * objectToWorld));
	vertexNormal = (normalMatrix * vec4(normal, 0)).xyz;
	vertexOriginalNormal = normal;
	vec3 vertexInViewSpace = (worldToView * objectToWorld * position).xyz;
	eyeDir = -vertexInViewSpace.xyz;
    
	vertexTexCoord = texCoord;

	vHeight = position[1];

	gl_Position = viewToClip * worldToView * objectToWorld * position; //WorldToView * vec4(vertexInCamSpace,1.0);
}
