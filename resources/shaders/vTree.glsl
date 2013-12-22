#version 330

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;
layout (location = 7) in vec3 instancePosition;

out vec3 vertexNormal;
out vec2 vertexTexCoord;
out vec4 vertexColor;   //Ikkje i bruk, men tatt med for debugging
out vec3 eyeDir;        //vektoren fraa camera (auget) til verteksen

uniform mat4 objectToWorld; //a.k.a model
uniform mat4 worldToView;   //a.k.a view
uniform mat4 viewToClip;    //a.k.a projection

void main() {
	mat4 normalMatrix = transpose(inverse(worldToView * objectToWorld));
	vertexNormal = (normalMatrix * vec4(normal, 0)).xyz;

	eyeDir = -(worldToView * objectToWorld * position).xyz;
    
	vertexTexCoord = texCoord;

	gl_Position = viewToClip * worldToView * objectToWorld * (position + vec4(instancePosition, 0.0f));
}
