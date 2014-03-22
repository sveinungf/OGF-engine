#pragma once

#include <vector>
#include "../ShaderLayout.h"
#include "../ShaderProgram.h"
#include "AbstractComponent.h"
#include "OGFConfig.h"


class Instancing : public AbstractComponent {

public:
	Instancing(const std::vector<glm::vec3>& instancePositions);
	Instancing(const std::vector<glm::vec3>& instancePositions, const std::vector<glm::vec3>& instanceNormals);
	virtual ~Instancing() override {}

	virtual void preRender(AbstractMesh* mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}

	int getVisibleInstances() const { return visibleInstances; }
private:
	int instances;
	int bytesOfInstancePositions;
	int bytesOfInstanceNormals;
	std::vector<glm::vec3> instancePositions;
	std::vector<glm::vec3> instanceNormals;

	GLuint cullVAO;
	GLuint cullBuffer;
	GLuint cullQuery;
	ShaderProgram cullingShader;

	//TFB = Transform Feedback Buffer
	GLuint positionsTFB;
	GLuint normalsTFB;
	int visibleInstances;

	void init();
};
