#pragma once

#include <vector>
#include "../ShaderLayout.h"
#include "../ShaderProgram.h"
#include "AbstractComponent.h"
#include "OGFConfig.h"


class Instancing : public AbstractComponent {

public:
	explicit Instancing(const std::vector<glm::vec3>& instancePositions);
	explicit Instancing(const std::vector<glm::vec3>& instancePositions, const std::vector<glm::vec3>& instanceNormals);
	virtual ~Instancing() override {}

	// Virtual constructor idiom
	virtual Instancing* clone() const override { return new Instancing(*this); }

	virtual void preRender(const std::shared_ptr<AbstractMesh>&, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(const std::shared_ptr<AbstractMesh>& mesh) override;
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
