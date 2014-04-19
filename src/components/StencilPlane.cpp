#include "components/StencilPlane.h"

using namespace glm;
using namespace std;


void StencilPlane::preRender(const shared_ptr<AbstractMesh>&, const mat4&, const mat4&, const mat4&) {
	glEnable(GL_RASTERIZER_DISCARD);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
}

void StencilPlane::postRender() {
	glStencilFunc(GL_EQUAL, 1, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_RASTERIZER_DISCARD);
}
