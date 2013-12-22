#version 410 core

uniform struct LightSource {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light[64];

uniform struct MaterialProperties {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} material;

uniform mat4 worldToView;   //a.k.a view
uniform int numberOfLights;

uniform sampler2D texArray[1];
uniform int textureId;
uniform int id;

in block {
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	vec2 texCoord;
	vec4 color;    //Ikkje i bruk, men tatt med for debugging
	vec3 V;        //vektoren fraa camera (auget) til verteksen
} inData;

out vec4 color;

vec3 encodeID (int id);

void main() 
{ 
	
	//Temp variables used to store values for each light (a.k.a each loop iteration)
	vec3 ambient = vec3(0);
	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	//Loop used to calculate the contribution from each light
	for (int i = 0; i < numberOfLights; i++) {
		//
		//    V = Vector from fragment to eye
		//    N = Fragment normal (in View space)
		//    L = Vector from fragment to light
		//    H = Half-vector between V and L
		//
		//    A diagramm is located in the --/solution/docs/ which illustrates the various vectors
		//
    
		vec3 lightInViewSpace = (worldToView * light[i].position).xyz;
		vec3 lightDir = lightInViewSpace - inData.V;

		vec3 N = normalize(inData.normal);

		vec3 L, H;
		L = normalize(lightDir);
		H = normalize(L - normalize(inData.V));

		ambient += light[i].ambient.xyz;
		diffuse += light[i].diffuse.xyz * max(dot(L, N),0);
		specular += light[i].specular.xyz * pow(max(dot(H, N), 0), material.shininess);
	};

	/*
	ambient *= material.ambient.xyz;
	diffuse *= material.diffuse.xyz;
	specular *= material.specular.xyz;
	*/

	if(id == 0){
		color = texture2D(texArray[0], inData.texCoord); // * vec4(ambient + diffuse + specular, 0.0); //vec4(0.5, 0.2, 0.2, 1.0);
	}else{
		color = vec4(encodeID(id),1.0f);
	}	
	// Link to the youtube tutorial: http://www.youtube.com/watch?v=msHV_y-RmaI
	// NB: In german but easy to follow. Even if you don't know how to speak german
    
} 