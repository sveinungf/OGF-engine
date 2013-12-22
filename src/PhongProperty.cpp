#include "PhongProperty.h"

PhongProperty::PhongProperty(const PhongProperty& other) : ambient(
        other.ambient), diffuse(other.diffuse), specular(other.specular),
    shininess(other.shininess) {
}

PhongProperty::PhongProperty(const glm::vec4& ambientRGBA,
                             const glm::vec4& diffuseRGBA, const glm::vec4& specularRGBA,
                             const GLfloat& shine) : ambient(ambientRGBA), diffuse(diffuseRGBA),
    specular(specularRGBA), shininess(shine) {
}

std::ostream& operator<< (std::ostream& output, const PhongProperty& prop) {
    output << glm::to_string(prop.ambient) << std::endl;
    output << glm::to_string(prop.diffuse) << std::endl;
    output << glm::to_string(prop.specular) << std::endl;
    output << prop.shininess << std::endl;

    return output;
}
