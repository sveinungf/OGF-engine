#include "components/SwitchableComponent.h"

using namespace glm;
using namespace std;


void SwitchableComponent::addComponent(const std::shared_ptr<AbstractComponent>& component) {
	components.push_back(component);
}

void SwitchableComponent::preRender(const shared_ptr<AbstractMesh>& mesh, const mat4& viewToClip, const mat4& worldToView, const mat4& objectToWorld) {
	components.at(currentIndex)->preRender(mesh, viewToClip, worldToView, objectToWorld);
}

void SwitchableComponent::render(const shared_ptr<AbstractMesh>& mesh) {
	components.at(currentIndex)->render(mesh);
}

void SwitchableComponent::postRender() {
	components.at(currentIndex)->postRender();

	if (autoNext) {
		next();
	}
}
