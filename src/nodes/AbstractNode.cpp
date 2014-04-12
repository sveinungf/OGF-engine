#include "nodes/AbstractNode.h"

using namespace glm;
using namespace std;


// Destructors
AbstractNode::~AbstractNode() {/*
    for (AbstractNode* const child : children) {
        delete child;
    }
	*/
	for (AbstractComponent* const component : components) {
		delete component;
	}

	if (phongProperty != nullptr) {
		delete phongProperty;
	}
}

// Scenegraph
void AbstractNode::add(const shared_ptr<AbstractNode>& child) {
    children.push_back(child);
}

// Components
void AbstractNode::addComponent(AbstractComponent* const component) {
    components.push_back(component);
}

// Inherited transformations
void AbstractNode::disableAllParentTransformations() {
    for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
        transformationFlags[i] = false;
    }
}

void AbstractNode::enableAllParentTransformations() {
    for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
        transformationFlags[i] = true;
    }
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
	transformations[TRANSLATION] = glm::translate(to - getPositionVec3());
}

void AbstractNode::setPosition(const GLfloat x, const GLfloat y, const GLfloat z) {
    setPosition(glm::vec3(x, y, z));
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
AbstractNode::AbstractNode() : phongProperty(nullptr) {
    for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
        transformationFlags[i] = true;
    }
}

AbstractNode::AbstractNode(const AbstractNode& other) : children(other.children.size()), components(other.components.size()), objectToWorld(other.objectToWorld), phongProperty(other.phongProperty == nullptr ? nullptr : new PhongProperty(*other.phongProperty)) {

	for (size_t i = 0; i < other.children.size(); ++i) {
		children[i] = shared_ptr<AbstractNode>(other.children[i]->clone());
	}

	for (size_t i = 0; i < other.components.size(); ++i) {
		components[i] = other.components[i]->clone();
	}

	for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
		transformationFlags[i] = other.transformationFlags[i];
		transformations[i] = other.transformations[i];
	}
}

// Transformations
mat4 AbstractNode::getParentObjectToWorld(mat4 parentTransformations[]) const {
    mat4 result;

    if (parentTransformations != nullptr) {
        for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
            if (transformationFlags[i]) {
                result *= parentTransformations[i];
            }
        }
    }

    return result;
}

void AbstractNode::updateObjectToWorld(mat4 parentTransformations[]) {
    mat4 result;

    transformations[OBJECT_TO_WORLD_PARENT] = getParentObjectToWorld(parentTransformations);

    for (int i = 0; i < MAX_TRANSFORMATIONS; ++i) {
        result *= transformations[i];
    }

    objectToWorld = result;
}

// Rendering
void AbstractNode::render(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	updateObjectToWorld(parentTransformations);
	renderSelf(worldToView, viewToClip);

	for (const auto& child : children) {
		child->render(worldToView, viewToClip, transformations);
	}
}

void AbstractNode::renderID(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) {
	updateObjectToWorld(parentTransformations);
	renderIDSelf(worldToView, viewToClip);

	for (const auto& child : children) {
		child->renderID(worldToView, viewToClip, transformations);
	}
}

// Friends
void swap(AbstractNode& first, AbstractNode& second) {
	// Enable ADL
	using std::swap;

	swap(first.children, second.children);
	swap(first.components, second.components);
	swap(first.transformationFlags, second.transformationFlags);
	swap(first.transformations, second.transformations);
	swap(first.objectToWorld, second.objectToWorld);
	swap(first.phongProperty, second.phongProperty);
}
