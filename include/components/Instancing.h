#pragma once

#include <vector>
#include "../ShaderLayout.h"
#include "../ShaderProgram.h"
#include "AbstractComponent.h"
#include "OGFConfig.h"

using namespace std;

#pragma warning(push)
#pragma warning(disable:4100) // ignore unused parameters

class Instancing : public AbstractComponent {

public:
	Instancing(const vector<vec3>& instancePositions);
	Instancing(const vector<vec3>& instancePositions, const vector<vec3>& instanceNormals);

	virtual void preRender(AbstractMesh* mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) override;
	virtual void render(AbstractMesh* mesh) override;
	virtual void postRender() override {}

	int getVisibleInstances() const { return visibleInstances; }
private:
	int instances;
	int bytesOfInstancePositions;
	int bytesOfInstanceNormals;
	vector<vec3> instancePositions;
	vector<vec3> instanceNormals;

	GLuint cullVAO;
	GLuint cullBuffer;
	GLuint cullQuery;
	ShaderProgram cullingShader;

	GLuint positionsTFB; // TFB = Transform Feedback Buffer
	GLuint normalsTFB;
	int visibleInstances;

	void init();
};

#pragma warning(pop)
