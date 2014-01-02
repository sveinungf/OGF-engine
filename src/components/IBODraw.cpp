#include "components/IBODraw.h"


void IBODraw::render(AbstractMesh* mesh) {
	glBindVertexArray(mesh->getVAO());
	glDrawElements(GL_TRIANGLES, mesh->getNumberOfIndices(), GL_UNSIGNED_INT, (GLvoid*) 0);
}
