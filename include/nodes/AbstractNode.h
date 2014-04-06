#pragma once

#include <vector>
#include <glmhppnowarnings.h>
#include "../components/AbstractComponent.h"
#include "../PhongProperty.h"


class AbstractNode {

public:
    enum Transformation {
        OBJECT_TO_WORLD_PARENT = 0,
        ROTATION_ORIGIN,
        TRANSLATION,
        ROTATION_SELF,
        SCALING,
        //-----------
        MAX_TRANSFORMATIONS
    };

    // Destructors
    virtual ~AbstractNode();

	// Virtual constructor idiom
	virtual AbstractNode* clone() const = 0;

    // Scenegraph
    void add(AbstractNode* const child);

    // Components
    void addComponent(AbstractComponent* const component);

    // Inherited transformations
    void disableAllParentTransformations();
    void enableAllParentTransformations();
    void disableParentTransformation(const Transformation transformation);
    void enableParentTransformation(const Transformation transformation);

    // Transformations
    glm::vec3 getPositionVec3() const;
    glm::vec4 getPositionVec4() const;
    void setPosition(const glm::vec3& xyz);
    void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);
    void move(const glm::vec3& xyz);
    void move(const GLfloat x, const GLfloat y, const GLfloat z);
    void rotateAroundOriginX(const GLfloat x);
    void rotateAroundOriginY(const GLfloat y);
    void rotateAroundOriginZ(const GLfloat z);
    void rotateAroundSelfX(const GLfloat x);
    void rotateAroundSelfY(const GLfloat y);
    void rotateAroundSelfZ(const GLfloat z);
    void scale(const glm::vec3& xyz);
    void scale(const GLfloat x, const GLfloat y, const GLfloat z);

    // PhongProperty
	PhongProperty* const getPhongProperty() { return phongProperty; };
	void setPhongProperty(PhongProperty* const prop) { phongProperty = prop; };

    // Rendering
    void render(const glm::mat4& worldToView, const glm::mat4& viewToClip, glm::mat4 parentTransformations[]);
	void renderID(const glm::mat4& worldToView, const glm::mat4& viewToClip, glm::mat4 parentTransformations[]);

	friend void swap(AbstractNode& first, AbstractNode& second);

protected:
    // Scenegraph
    std::vector<AbstractNode* const> children;

    // Components
    std::vector<AbstractComponent* const> components;

    // Inherited transformations
    bool transformationFlags[MAX_TRANSFORMATIONS];

    // Transformations
    glm::mat4 transformations[MAX_TRANSFORMATIONS];
    glm::mat4 objectToWorld;

    // PhongProperty
	PhongProperty* phongProperty;


    /* Protected methods */

    // Constructors
    AbstractNode();
	AbstractNode(const AbstractNode& other);

    // Transformations
    glm::mat4 getParentObjectToWorld(glm::mat4 parentTransformations[]) const;
    void updateObjectToWorld(glm::mat4 parentTransformations[]);

	// Rendering
	virtual void renderSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) = 0;
	virtual void renderIDSelf(const glm::mat4& worldToView, const glm::mat4& viewToClip) = 0;
};
