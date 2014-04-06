#include "PhongProperty.h"

using namespace glm;
using namespace std;


PhongProperty::PhongProperty(const vec4& ambientRGBA, const vec4& diffuseRGBA, const vec4& specularRGBA, const GLfloat shine)
		: ambient(ambientRGBA), diffuse(diffuseRGBA), specular(specularRGBA), shininess(shine) {
}

ostream& operator<<(ostream& output, const PhongProperty& prop) {
	output << to_string(prop.ambient) << endl;
	output << to_string(prop.diffuse) << endl;
	output << to_string(prop.specular) << endl;
	output << prop.shininess << endl;

	return output;
}
