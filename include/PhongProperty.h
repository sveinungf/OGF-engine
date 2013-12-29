#pragma once

#include <ostream>
#include <GL/glew.h>
#include <glmhppnowarnings.h>
#include <glm/ext.hpp>


class PhongProperty {

public:
	PhongProperty(const PhongProperty& other);
	PhongProperty(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, const GLfloat& shininess);

	const glm::vec4& getAmbient() const { return ambient; }
	const glm::vec4& getDiffuse() const { return diffuse; }
	const glm::vec4& getSpecular() const { return specular; }
	const GLfloat& getShininess() const { return shininess; }
	void setAmbient(const glm::vec4& amb) { ambient = amb; }
	void setDiffuse(const glm::vec4& dif) { diffuse = dif; }
	void setSpecular(const glm::vec4& spec) { specular = spec; }
	void setShininess(const GLfloat& shin) { shininess = shin; }

	friend std::ostream& operator<< (std::ostream & output, const PhongProperty &prop);

private:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    GLfloat shininess;
};
