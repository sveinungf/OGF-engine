#include "LightProperties.h"

/*
	Correct order of property vectors in each light
	...= PhongProperty(
		glm::vec4(<ambientvalues>),
		glm::vec4(<diffusevalues>),
		glm::vec4(<specularvalues>),
		GLfloat (will be ignored)
	);
*/

PhongProperty LightProperties::BLUE = PhongProperty(
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    0.0f
);

PhongProperty LightProperties::GREEN = PhongProperty(
    glm::vec4(0.0f, 0.2f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.2f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    0.0f
);

PhongProperty LightProperties::RED = PhongProperty(
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
    0.0f
);

PhongProperty LightProperties::STREETLIGHT = PhongProperty(
	glm::vec4(0.25f, 0.25f, 0.25f, 1.0f),
	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	0.0f
);

PhongProperty LightProperties::SUNLIGHT = PhongProperty(
	glm::vec4(0.1f, 0.1f, 0.1f, 0.0f),
	glm::vec4(0.94f, 0.90f, 0.54f, 0.0f),
	glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
	0.0f
);

PhongProperty LightProperties::WHITE = PhongProperty(
	glm::vec4(0.1f, 0.1f, 0.1f, 0.0f),
	glm::vec4(1.0f, 1.0f, 1.0f, 0.0f),
	glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
	0.0f
	);

PhongProperty LightProperties::DEBUG_NO_AMBIENT = PhongProperty(
	glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
	glm::vec4(0.94f, 0.90f, 0.64f, 0.0f),
	glm::vec4(1.0f, 1.0f, 0.9f, 0.0f),
	0.0f
	);