#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glmhppnowarnings.h>
#include "PhongProperty.h"
#include "TerrainContentData.h"


class Shader {

public:
	enum {
		FRAG = GL_FRAGMENT_SHADER,
		VERT = GL_VERTEX_SHADER,
		GEOM = GL_GEOMETRY_SHADER,
		LINK
	};

	Shader() : type(LINK) {}
	Shader(const std::string& thePath, const GLenum& theType) : path(thePath), type(theType) {}

	const std::string& getPath() const { return path; }
	const GLenum& getType() const { return type; }

private:
	std::string path;
	GLenum type;
};

class ShaderProgram {
	
public:
	ShaderProgram() { 
		std::cout << std::endl << "Creating shader:" << std::endl;
		programLocation = glCreateProgram(); 
	}

	ShaderProgram& operator<<(const Shader& shader);
	ShaderProgram& operator<<(const GLenum& type);

	const GLuint& getProgramLocation() const { return programLocation; }

	void use() const { glUseProgram(programLocation); }

	void setObjectToClip(const glm::mat4& matrix) const { setUniformMat4("objectToClip", matrix); }
	void setObjectToWorld(const glm::mat4& matrix) const { setUniformMat4("objectToWorld", matrix); }
	void setWorldToView(const glm::mat4& matrix) const { setUniformMat4("worldToView", matrix); }
	void setViewToClip(const glm::mat4& matrix) const { setUniformMat4("viewToClip", matrix); }

	void setTextureId(const GLuint& id) const;

	void setMaterialProperty(const PhongProperty& materialProperty) const;
	void setLightProperty(const PhongProperty&	lightProperty, const glm::vec4& position, const int& indexInArray) const;
	void setLightPosition(const glm::vec4& position, const int& indexInArray) const;

	void setTerrainContentData(const TerrainContentData& contentData) const;

	void setUniformGLint(const std::string& variable, const GLint& value) const;
    void setUniformGLfloat(const std::string& variable, const GLfloat& value) const;
    void setUniformMat4(const std::string& variable, const glm::mat4& value) const;
	void setUniformVec3(const std::string& variable, const glm::vec3& value) const;
    void setUniformVec4(const std::string& variable, const glm::vec4& value) const;

	void setTransformFeedbackOutput(const std::vector<std::string>& varyings) const;
private:
    GLuint programLocation;
};
