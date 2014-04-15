#include "nodes/AbstractNode.h"

using namespace glm;
using namespace std;


// Scenegraph
void AbstractNode::add(const shared_ptr<AbstractNode>& child) {
    children.push_back(child);
}

// Components
void AbstractNode::addComponent(const shared_ptr<AbstractComponent>& component) {
    components.push_back(component);
}

// Inherited transformations
void AbstractNode::disableAllParentTransformations() {
	transformationFlags.fill(false);
}

void AbstractNode::enableAllParentTransformations() {
	transformationFlags.fill(true);
}

void AbstractNode::disableParentTransformation(const Transformation transformation) {
    transformationFlags[transformation] = false;
}

void AbstractNode::enableParentTransformation(const Transformation transformation) {
    transformationFlags[transformation] = true;
}

// Transformations
glm::vec3 AbstractNode::getPositionVec3() const {
    return glm::vec3(getPositionVec4());
}

glm::vec4 AbstractNode::getPositionVec4() const {
    return objectToWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void AbstractNode::setPosition(const glm::vec3& to) {
	transformations[TRANSLATION] = glm::translate(to);
}

void AbstractNode::setPosition(const GLfloat x, const GLfloat y, const GLfloat z) {
	transformations[TRANSLATION] = glm::translate(x, y, z);
}

void AbstractNode::move(const glm::vec3& xyz) {
    transformations[TRANSLATION] *= glm::translate(xyz);
}

void AbstractNode::move(const GLfloat x, const GLfloat y, const GLfloat z) {
    transformations[TRANSLATION] *= glm::translate(x, y, z);
}

void AbstractNode::rotateAroundOriginX(const GLfloat x) {
    transformations[ROTATION_ORIGIN] *= glm::rotate(x, 1.0f, 0.0f, 0.0f);
}

void AbstractNode::rotateAroundOriginY(const GLfloat y) {
    transformations[ROTATION_ORIGIN] *= glm::rotate(y, 0.0f, 1.0f, 0.0f);
}

void AbstractNode::rotateAroundOriginZ(const GLfloat z) {
    transformations[ROTATION_ORIGIN] *= glm::rotate(z, 0.0f, 0.0f, 1.0f);
}

void AbstractNode::rotateAroundSelfX(const GLfloat x) {
    transformations[ROTATION_SELF] *= glm::rotate(x, 1.0f, 0.0f, 0.0f);
}

void AbstractNode::rotateAroundSelfY(const GLfloat y) {
    transformations[ROTATION_SELF] *= glm::rotate(y, 0.0f, 1.0f, 0.0f);
}

void AbstractNode::rotateAroundSelfZ(const GLfloat z) {
    transformations[ROTATION_SELF] *= glm::rotate(z, 0.0f, 0.0f, 1.0f);
}

void AbstractNode::scale(const glm::vec3& xyz) {
    transformations[SCALING] *= glm::scale(xyz);
}

void AbstractNode::scale(const GLfloat x, const GLfloat y, const GLfloat z) {
    transformations[SCALING] *= glm::scale(x, y, z);
}


/* Protected methods */

// Constructors
AbstractNode::AbstractNode() {
	transformationFlags.fill(true);
}

// Transformations
mat4 AbstractNode::getParentObjectToWorld(const array<mat4, MAX_TRANSFORMATIONS>* const parentTransformations) const {
    mat4 result;

    if (parentTransformations != nullptr) {
        for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
            if (transformationFlags[i]) {
                result *= parentTransformations->at(i);
            }
        }
    }

    return result;
}

void AbstractNode::updateObjectToWorld(const array<mat4, MAX_TRANSFORMATIONS>* const parentTransformations) {
    mat4 result;

    transformations[OBJECT_TO_WORLD_PARENT] = getParentObjectToWorld(parentTransformations);

    for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
        result *= transformations[i];
    }

    objectToWorld = result;
}

// Rendering
void AbstractNode::render(const mat4& worldToView, const mat4& viewToClip, const array<mat4, MAX_TRANSFORMATIONS>* const parentTransformations) {
	updateObjectToWorld(parentTransformations);
	renderSelf(worldToView, viewToClip);

	for (const auto& child : children) {
		child->render(worldToView, viewToClip, &transformations);
	}
}

void AbstractNode::renderID(const mat4& worldToView, const mat4& viewToClip, const array<mat4, MAX_TRANSFORMATIONS>* const parentTransformations) {
	updateObjectToWorld(parentTransformations);
	renderIDSelf(worldToView, viewToClip);

	for (const auto& child : children) {
		child->renderID(worldToView, viewToClip, &transformations);
	}
}
