#include "components/SimpleDraw.h"


void SimpleDraw::render(const std::shared_ptr<AbstractMesh>& mesh) {
	glBindVertexArray(mesh->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, mesh->getNumberOfVertices());
}
