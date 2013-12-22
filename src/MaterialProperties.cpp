#include "MaterialProperties.h"

/*
	Correct order of property vectors in each material
	...= PhongProperty(
		glm::vec4(<ambientvalues>),
		glm::vec4(<diffusevalues>),
		glm::vec4(<specularvalues>),
		GLfloat <shininessvalues>
	);
*/

float MaterialProperties::SHININESS_FACTOR = 128.0f;

PhongProperty MaterialProperties::GOLD = PhongProperty(
            glm::vec4(0.24725f, 0.1995f, 0.0745f, 1.0f),
            glm::vec4(0.75164f, 0.60648f, 0.22648f, 1.0f),
            glm::vec4(0.628281f, 0.555802f, 0.366065f, 1.0f),
			0.4f * SHININESS_FACTOR
        );

PhongProperty MaterialProperties::OBSIDIAN = PhongProperty(
            glm::vec4(0.05375f, 0.05f, 0.06475f, 1.0f),
            glm::vec4(0.4f, 0.2368f, 0.1036f, 1.0f),
            glm::vec4(0.774597f, 0.458561f, 0.200621f, 1.0f),
			0.3f * SHININESS_FACTOR
        );

PhongProperty MaterialProperties::PLASTIC_RED = PhongProperty(
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.5f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.7f, 0.6f, 0.6f, 1.0f),
			0.25f * SHININESS_FACTOR
        );

PhongProperty MaterialProperties::POLISHED_BRONZE = PhongProperty(
            glm::vec4(0.25f, 0.148f, 0.06625f, 1.0f),
            glm::vec4(0.18275f, 0.17f, 0.22525f, 1.0f),
            glm::vec4(0.332741f, 0.328634f, 0.346435f, 1.0f),
			1.0f * SHININESS_FACTOR
        );

PhongProperty MaterialProperties::RUBBER_GREEN = PhongProperty(
            glm::vec4(0.0f, 0.05f, 0.0f, 1.0f),
            glm::vec4(0.4f, 0.5f, 0.4f, 1.0f),
            glm::vec4(0.04f, 0.7f, 0.04f, 1.0f),
			0.078125f * SHININESS_FACTOR
        );

PhongProperty MaterialProperties::SILVER = PhongProperty(
            glm::vec4(0.19225f, 0.19225f, 0.19225f, 1.0f),
            glm::vec4(0.50754f, 0.50754f, 0.50754f, 1.0f),
            glm::vec4(0.508273f, 0.508273f, 0.508273f, 1.0f),
			0.4f * SHININESS_FACTOR
        );
