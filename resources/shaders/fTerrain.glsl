#version 330 

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
uniform sampler2D texArray[4];

uniform float waterHeight;
uniform float rockHeight;
uniform float snowHeight;
uniform float mixRange;

uniform int id;
uniform int discardUnderWater;

in vec4 vertexColor;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec3 vertexOriginalNormal;
in vec3 eyeDir;

in float vHeight;

out vec4 color;

vec3 encodeID (int id);

void main() { 
	float sandGrassMixRange = 2.0f;
	//Temp variables used to store values for each light (a.k.a each loop iteration)
	vec3 ambient = vec3(0);
	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	//Loop used to calculate the contribution from each light
	for (int i = 0; i < numberOfLights; i++) {
		//
		//    E = Vector from fragment to eye
		//    N = Fragment normal (in View space)
		//    L = Vector from fragment to light
		//    H = Half-vector between E and L
		//
		//    A diagramm is located in the --/solution/docs/ which illustrates the various vectors
		//
    
		vec3 lightInViewSpace = (worldToView * light[i].position).xyz;
		vec3 lightDir = lightInViewSpace - (-eyeDir);

		vec3 E = normalize(eyeDir);
		vec3 N = normalize(vertexNormal);

		vec3 L, H;
		L = normalize(lightDir);
		H = normalize(E + L);

		ambient += light[i].ambient.xyz;
		diffuse += light[i].diffuse.xyz * max(dot(L, N),0);
		specular += light[i].specular.xyz * pow(max(dot(H, N), 0), material.shininess);
	};

	//ambient *= material.ambient.xyz;
	//diffuse *= material.diffuse.xyz;
	//specular *= material.specular.xyz;

	vec4 textureColor;
	
	if (discardUnderWater == 1 && vHeight < waterHeight) {
		discard;
	} else if (vHeight < waterHeight - sandGrassMixRange) {		// sand
		textureColor = texture2D(texArray[0], vertexTexCoord);
	} else if (vHeight < waterHeight + sandGrassMixRange) {		// mix between sand and grass
		float mixFactor = (vHeight - waterHeight + sandGrassMixRange) / (2.0f * sandGrassMixRange);
		textureColor = mix(texture2D(texArray[0], vertexTexCoord), texture2D(texArray[1], vertexTexCoord), mixFactor);
	} else if (vHeight < rockHeight - mixRange) {				// grass
		textureColor = texture2D(texArray[1], vertexTexCoord);
	} else if (vHeight < rockHeight + mixRange) {				// mix between grass and rock
		float mixFactor = (vHeight - rockHeight + mixRange) / (2.0f * mixRange);
		textureColor = mix(texture2D(texArray[1], vertexTexCoord), texture2D(texArray[2], vertexTexCoord), mixFactor);
	} else if (vHeight < snowHeight - mixRange) {				// rock
		if(vertexOriginalNormal.y < 0.85f){
			textureColor = mix(texture2D(texArray[2], vertexTexCoord), texture2D(texArray[1], vertexTexCoord), 0.01f);
		}else if (vertexOriginalNormal.y < 0.8f){
			textureColor = mix(texture2D(texArray[2], vertexTexCoord), texture2D(texArray[1], vertexTexCoord), 0.12f);
		}else if(vertexOriginalNormal.y < 0.7){
			textureColor = mix(texture2D(texArray[2], vertexTexCoord), texture2D(texArray[1], vertexTexCoord), 0.15f);
		}else{
			textureColor = mix(texture2D(texArray[2], vertexTexCoord), texture2D(texArray[1], vertexTexCoord), 0.17f);
		}
		
	} else if (vHeight < snowHeight + mixRange) {				// mix between rock and snow
		float mixFactor = (vHeight - snowHeight + mixRange) / (2.0f * mixRange);
		textureColor = mix(texture2D(texArray[2], vertexTexCoord), texture2D(texArray[3], vertexTexCoord), mixFactor);
	} else {													// snow
		textureColor = texture2D(texArray[3], vertexTexCoord);
	}

	if (id == 0) {
		color = textureColor * vec4(ambient + diffuse + specular, 1.0f);
	} else {
		color = vec4(encodeID(id), 1.0f);
	}	
}
