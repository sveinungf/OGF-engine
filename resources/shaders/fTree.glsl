#version 330 

uniform struct LightSource {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light[64];

uniform mat4 worldToView;
uniform int numberOfLights;

uniform sampler2D texture[1];
uniform int textureId;

uniform int id;

in vec4 vertexColor;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec3 eyeDir;
in vec3 lightDir;

out vec4 color;

vec3 encodeID (int id);

void main() { 
	vec4 textureColor = texture2D(texture[0], vertexTexCoord);

	if (textureColor.a < 0.5f) {
		discard;
	} else {
		textureColor.a = 1.0f;
	}

	vec3 ambient = vec3(0.0f);
	vec3 diffuse = vec3(0.0f);
	vec3 specular = vec3(0.0f);

	for (int i = 0; i < numberOfLights; ++i) {
		vec3 lightInViewSpace = (worldToView * light[i].position).xyz;
		vec3 lightDir = lightInViewSpace + eyeDir;

		vec3 E = normalize(eyeDir);
		vec3 N = normalize(vertexNormal);

		vec3 L = normalize(lightDir);
		vec3 H = normalize(E + L);

		ambient += light[i].ambient.xyz;
		diffuse += light[i].diffuse.xyz * max(dot(L, N),0);
		specular += light[i].specular.xyz * pow(max(dot(H, N), 0), 0.0f); //Hardcoded shininess
	}

	if (id == 0) {
		color = textureColor * vec4(ambient + diffuse + specular, 1.0f);
	} else {
		color = vec4(encodeID(id),1.0f);
	}	
}
