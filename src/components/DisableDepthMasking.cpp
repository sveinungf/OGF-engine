#include "components/DisableDepthMasking.h"


void DisableDepthMasking::preRender(AbstractMesh*, const glm::mat4&, const glm::mat4&, const glm::mat4&) {
	glDepthMask(GL_FALSE);
}

void DisableDepthMasking::postRender() {
	glDepthMask(GL_TRUE);
}
