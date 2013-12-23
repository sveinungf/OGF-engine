#include "AbstractNode.h"
#include "MeshNode.h"

class AssImpNode : public AbstractNode {

public:
	AssImpNode(const ShaderProgram& program, const std::string& path);
	~AssImpNode();

	void addComponent(AbstractComponent* component, int mesh = -1);
	void setMaterial(PhongProperty* material, int mesh = -1);
	void addTexture(Texture2D* texture, int mesh = -1);

protected:
	// Rendering
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) override;

private:
	vector<MeshNode*> self;
};
