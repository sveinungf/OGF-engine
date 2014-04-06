#include <memory>
#include "../Texture2D.h"
#include "AbstractNode.h"
#include "MeshNode.h"


class AssImpNode : public AbstractNode {

public:
	explicit AssImpNode(const ShaderProgram& program, const std::string& path);

	// Virtual constructor idiom
	virtual AssImpNode* clone() const override { return new AssImpNode(*this); }

	virtual ~AssImpNode() override {}

	void addComponent(AbstractComponent* const component, const int mesh = -1);
	void setMaterial(PhongProperty* const material, const int mesh = -1);
	void addTexture(const std::shared_ptr<Texture>& texture, const int mesh = -1);

protected:
	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) override;

private:
	std::vector<MeshNode> self;
};
