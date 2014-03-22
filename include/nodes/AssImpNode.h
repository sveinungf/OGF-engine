#include "AbstractNode.h"
#include "MeshNode.h"


class AssImpNode : public AbstractNode {

public:
	explicit AssImpNode(const ShaderProgram& program, const std::string& path);
	virtual ~AssImpNode() override;

	void addComponent(AbstractComponent* component, int mesh = -1);
	void setMaterial(PhongProperty* material, int mesh = -1);
	void addTexture(Texture2D* texture, int mesh = -1);

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;

private:
	std::vector<MeshNode*> self;
};
