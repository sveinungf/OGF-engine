#version 330 

in vec4 vPosition;
in vec2 vTexCoord2;
in vec3 vTexCoord3;

uniform struct LightSource {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light[1];

uniform samplerCube cubeTexture;
uniform sampler2D texArray[3];
uniform int id;

out vec4 fColor;

vec3 encodeID(int id);

void main() {
	vec3 V = normalize(vPosition.xyz);
    vec3 L = normalize(light[0].position.xyz);

    // Compute the proximity of this fragment to the sun.
    float vl = dot(V, L);

    // Look up the sky color and glow colors.
	float horizont = 0.5f;
    vec4 Kcolor = texture2D(texArray[1], vec2((L.y + 1.0) / 2.0, V.y + horizont));
    vec4 Kglow = texture2D(texArray[2], vec2((L.y + 1.0) / 2.0, vl));

    // Combine the color and glow giving the pixel value.
    vec4 combined = vec4(Kcolor.rgb + Kglow.rgb * Kglow.a / 2.0, Kcolor.a);
	
	vec4 stars = texture(cubeTexture, vPosition.xyz);	

	if (id == 0) {
		fColor = vec4(combined.rgb * combined.a + stars.rgb * (stars.a - combined.a), 1.0f);
	} else {
		fColor = vec4(encodeID(id), 1.0f);
	}
} 
