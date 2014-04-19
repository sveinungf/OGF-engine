#pragma once

#include <memory>
#include <vector>
#include "AbstractComponent.h"


class SwitchableComponent : public AbstractComponent {

public:
	explicit SwitchableComponent(const bool autoSwitch = true) : autoNext(autoSwitch), currentIndex(0) {}
	virtual ~SwitchableComponent() override {}

	// Virtual constructor idiom
	virtual SwitchableComponent* clone() const override { return new SwitchableComponent(*this); }

	void addComponent(const std::shared_ptr<AbstractComponent>& component);
	void next() { currentIndex = (currentIndex + 1) % components.size(); }

	virtual void preRender(const std::shared_ptr<AbstractMesh>& mesh, const glm::mat4& viewToClip, const glm::mat4& worldToView, const glm::mat4& objectToWorld) override;
	virtual void render(const std::shared_ptr<AbstractMesh>& mesh) override;
	virtual void postRender() override;
	
private:
	bool autoNext;
	size_t currentIndex;
	std::vector<std::shared_ptr<AbstractComponent>> components;
};
