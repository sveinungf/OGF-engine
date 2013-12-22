#include "components/SimpleDraw.h"


void SimpleDraw::render(AbstractMesh* mesh) {
	glBindVertexArray(mesh->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, mesh->getNumberOfVertices());
}
