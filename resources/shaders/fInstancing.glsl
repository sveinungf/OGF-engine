#version 330 

in vec4 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 eyeDir;

uniform struct LightSource {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light[64];

uniform mat4 worldToView;
uniform int numberOfLights;
uniform sampler2D texArray[1];

uniform int id;

out vec4 fColor;  //Color out for this fragment

vec3 encodeID (int id);

void main() {
	vec4 textureColor = texture2D(texArray[0], vTexCoord);

	if (textureColor.a < 0.9f) {
		discard;
	}

	vec3 ambient = vec3(0.0f);
	vec3 diffuse = vec3(0.0f);
	vec3 specular = vec3(0.0f);

	for (int i = 0; i < numberOfLights; ++i) {
		vec3 lightInViewSpace = (worldToView * light[i].position).xyz;
		vec3 lightDir = lightInViewSpace + eyeDir;

		vec3 E = normalize(eyeDir);
		vec3 N = normalize(vNormal);

		vec3 L = normalize(lightDir);
		vec3 H = normalize(E + L);

		ambient += light[i].ambient.xyz;
		diffuse += light[i].diffuse.xyz * max(dot(L, N),0);
		specular += light[i].specular.xyz * pow(max(dot(H, N), 0), 0.0f); // Hardcoded shininess
	};

	if(id == 0){
		fColor = textureColor * vec4(ambient + diffuse + specular, 1.0f);
	}else{
		fColor = vec4(encodeID(id),1.0f);
	}	
} 
