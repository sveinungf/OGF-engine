#include "components/Blending.h"


void Blending::preRender(AbstractMesh*, const mat4&, const mat4&, const mat4&) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Blending::postRender() {
	glDisable(GL_BLEND);
}
