#pragma once

#include <vector>
#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm/glm.hpp>
#pragma warning(pop)
#include "../components/AbstractComponent.h"
#include "../PhongProperty.h"

using namespace glm;
using namespace std;


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

    // Scenegraph
    void add(AbstractNode* child);

    // Components
    void addComponent(AbstractComponent* component);

    // Inherited transformations
    void disableAllParentTransformations();
    void enableAllParentTransformations();
    void disableParentTransformation(const Transformation& transformation);
    void enableParentTransformation(const Transformation& transformation);

    // Transformations
    glm::vec3 getPositionVec3() const;
    glm::vec4 getPositionVec4() const;
    void setPosition(const glm::vec3& xyz);
    void setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void move(const glm::vec3& xyz);
    void move(const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void rotateAroundOriginX(const GLfloat& x);
    void rotateAroundOriginY(const GLfloat& y);
    void rotateAroundOriginZ(const GLfloat& z);
    void rotateAroundSelfX(const GLfloat& x);
    void rotateAroundSelfY(const GLfloat& y);
    void rotateAroundSelfZ(const GLfloat& z);
    void scale(const glm::vec3& xyz);
    void scale(const GLfloat& x, const GLfloat& y, const GLfloat& z);

    // PhongProperty
	PhongProperty* getPhongProperty() { return phongProperty; };
	void setPhongProperty(PhongProperty* prop) { phongProperty = prop; };

    // Rendering
    void render(const mat4& worldToView, const mat4& viewToClip) { render(worldToView, viewToClip, nullptr); }
    void render(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]);

	void renderID(const mat4& worldToView, const mat4& viewToClip) { renderID(worldToView, viewToClip, nullptr); }
	void renderID(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]);

protected:
    // Scenegraph
    vector<AbstractNode*> children;

    // Components
    vector<AbstractComponent*> components;

    // Inherited transformations
    bool transformationFlags[MAX_TRANSFORMATIONS];

    // Transformations
    mat4 transformations[MAX_TRANSFORMATIONS];
    mat4 objectToWorld;

    // PhongProperty
	PhongProperty* phongProperty;


    /* Protected methods */

    // Constructors
    AbstractNode();

    // Transformations
    mat4 getParentObjectToWorld(mat4 parentTransformations[]) const;
    void updateObjectToWorld(mat4 parentTransformations[]);

	// Rendering
	virtual void renderSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) = 0;
	virtual void renderIDSelf(const mat4& worldToView, const mat4& viewToClip, mat4 parentTransformations[]) = 0;

};