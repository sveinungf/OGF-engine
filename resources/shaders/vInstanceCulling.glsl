#version 330

layout (location = 7) in vec3 instancePosition;
layout (location = 8) in vec3 instanceNormal;

out vec3 origPosition;
out vec3 origNormal;
flat out int objectVisible; // flat = no interpolation

uniform mat4 objectToClip;
uniform vec3 objectPositiveExtent = vec3(0.0f);
uniform vec3 objectNegativeExtent = vec3(0.0f);

void main() {
	origPosition = instancePosition;
	origNormal = instanceNormal;

	vec4 boundingBox[8];
	boundingBox[0] = objectToClip * vec4(instancePosition + objectPositiveExtent, 1.0f);
	boundingBox[1] = objectToClip * vec4(instancePosition + vec3(-objectNegativeExtent.x,   objectPositiveExtent.yz), 1.0f);
	boundingBox[2] = objectToClip * vec4(instancePosition + vec3( objectPositiveExtent.x,  -objectNegativeExtent.y,  objectPositiveExtent.z), 1.0f);
	boundingBox[3] = objectToClip * vec4(instancePosition + vec3(-objectNegativeExtent.xy,  objectPositiveExtent.z),  1.0f);
	boundingBox[4] = objectToClip * vec4(instancePosition + vec3( objectPositiveExtent.xy, -objectNegativeExtent.z),  1.0f);
	boundingBox[5] = objectToClip * vec4(instancePosition + vec3(-objectNegativeExtent.x,   objectPositiveExtent.y, -objectNegativeExtent.z), 1.0f);
	boundingBox[6] = objectToClip * vec4(instancePosition + vec3( objectPositiveExtent.x,  -objectNegativeExtent.yz), 1.0f);
	boundingBox[7] = objectToClip * vec4(instancePosition - objectNegativeExtent, 1.0f);
	
	int outOfBound[6] = int[6](0, 0, 0, 0, 0, 0);

	for (int i = 0; i < 8; ++i) {
		if (boundingBox[i].x >  boundingBox[i].w) ++outOfBound[0];
		if (boundingBox[i].x < -boundingBox[i].w) ++outOfBound[1];
		if (boundingBox[i].y >  boundingBox[i].w) ++outOfBound[2];
		if (boundingBox[i].y < -boundingBox[i].w) ++outOfBound[3];
		if (boundingBox[i].z >  boundingBox[i].w) ++outOfBound[4];
		if (boundingBox[i].z < -boundingBox[i].w) ++outOfBound[5];
	}

	bool inFrustum = true;

	for (int i = 0; i < 6; ++i) {
		if (outOfBound[i] == 8) {
			inFrustum = false;
		}
	}

	objectVisible = inFrustum ? 1 : 0;
}
