#version 330

uniform int idMul = 1;

vec3 encodeID (int id) {
	id = id * idMul;
	int r = id / 65536;
	r = max (r, 0);
	int g = (id - r * 65536) / 256;
	g = max (g, 0);
	int b = (id - r * 65536 - g * 256);
	b = max (b, 0);

	return vec3 (r / 255.0f, g / 255.0f, b / 255.0f);
}