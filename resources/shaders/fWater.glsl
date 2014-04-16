#version 330 

in vec3 pos_eye;
in vec3 n_eye;
in vec2 vertexTexCoord;
in vec4 texCoordProject;


in vec3 vNormal;
in vec3 eyeDir;

uniform sampler2D texArray[1];
uniform mat4 worldToView;
uniform int numberOfLights;
uniform int id;

uniform struct LightSource {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light[64];

out vec4 color;

vec3 encodeID (int id);

void main() { 
	/* reflect ray around normal from eye to surface */
	vec3 incident_eye = normalize(pos_eye);
	vec3 normal = normalize(n_eye);

	vec3 reflected = reflect(incident_eye, normal);
	// convert from eye to world space
	reflected = vec3(inverse(worldToView) * vec4(reflected, 0.0f));

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
	
	if (id == 0) {
		//color = vec4(mix(texture(cube_texture, reflected), vec4(0.0f, 0.8f, 0.8f, 1.0f), 0.3f).xyz, 0.8f);
		vec4 waterColor = vec4(0.0f, 0.8f, 0.8f, 1.0f) * vec4(ambient + diffuse + specular, 1.0f);
		color = vec4(mix(texture2DProj(texArray[0], texCoordProject).xyz, waterColor.xyz, 0.2f), 0.8f);
	} else {
		color = vec4(encodeID(id), 1.0f);
	}
}
