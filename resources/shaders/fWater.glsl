#version 330 

in vec3 pos_eye;
in vec3 n_eye;

uniform samplerCube cube_texture;
uniform mat4 worldToView;
uniform int id;

out vec4 color;

vec3 encodeID (int id);

void main() { 
	/* reflect ray around normal from eye to surface */
	vec3 incident_eye = normalize(pos_eye);
	vec3 normal = normalize(n_eye);

	vec3 reflected = reflect(incident_eye, normal);
	// convert from eye to world space
	reflected = vec3(inverse(worldToView) * vec4(reflected, 0.0f));

	if (id == 0) {
		color = vec4(mix(texture(cube_texture, reflected), vec4(0.0f, 0.8f, 0.8f, 1.0f), 0.3f).xyz, 0.8f);
	} else {
		color = vec4(encodeID(id), 1.0f);
	}
}
