#include "components/Blending.h"

#pragma warning(push)
#pragma warning(disable:4100) // ignore unused parameters
void Blending::preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
#pragma warning(pop)

void Blending::postRender() {
	glDisable(GL_BLEND);
}
