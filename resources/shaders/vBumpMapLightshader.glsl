#version 410 core

layout (location = 1) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in vec2 texCoord;
layout (location = 5) in vec3 tangent;
layout (location = 6) in vec3 bitangent;

uniform mat4 objectToWorld; //a.k.a model
uniform mat4 worldToView;   //a.k.a view
uniform mat4 viewToClip;    //a.k.a projection

out block {
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	vec2 texCoord;
	vec4 color;   //Ikkje i bruk, men tatt med for debugging
	vec3 V;        //vektoren fraa camera (auget) til verteksen
} outData;

void main()
{
    // Bring vectors into view space,
	// objectToView created once in order to minimize matrix operations in the shader
	mat4 objectToView = worldToView * objectToWorld;
	mat4 vectorToView = transpose(inverse(objectToView));
	outData.normal = (vectorToView * vec4(normal, 0.0f)).xyz;
	outData.tangent = (vectorToView * vec4(tangent, 0.0f)).xyz;
	outData.bitangent = (vectorToView * vec4(bitangent, 0.0f)).xyz;

	outData.texCoord = texCoord;
	outData.color = color;

	// vector from the vertex to the observer
	// V component in the Blinn-Phong lighting model
	outData.V = (objectToView * position).xyz;

	gl_Position = viewToClip * objectToView * position;
	// Vectors based on solutiondir-docs-800px-Blinn-Phong_Vectors.svg.png
    
}