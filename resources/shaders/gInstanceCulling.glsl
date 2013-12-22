#version 330

layout(points) in;
layout(points, max_vertices = 1) out;

in vec3 origPosition[1];
in vec3 origNormal[1];
flat in int objectVisible[1];

out vec3 culledPosition;
out vec3 culledNormal;

void main() {
	if (objectVisible[0] == 1) {
		culledPosition = origPosition[0];
		culledNormal = origNormal[0];
		EmitVertex();
		EndPrimitive();
	}
}