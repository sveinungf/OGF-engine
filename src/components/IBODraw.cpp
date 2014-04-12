#include "components/IBODraw.h"


void IBODraw::render(const std::shared_ptr<AbstractMesh>& mesh) {
	glBindVertexArray(mesh->getVAO());
	glDrawElements(GL_TRIANGLES, mesh->getNumberOfIndices(), GL_UNSIGNED_INT, (GLvoid*) 0);
}
