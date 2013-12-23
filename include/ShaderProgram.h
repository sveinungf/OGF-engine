#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <GL/glew.h>
#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "PhongProperty.h"
#include "TerrainContentData.h"


using namespace glm;
using namespace std;


class Shader {

public:
	enum {
		FRAG = GL_FRAGMENT_SHADER,
		VERT = GL_VERTEX_SHADER,
		GEOM = GL_GEOMETRY_SHADER,
		LINK
	};

	Shader() : type(LINK) {}
	Shader(const string& thePath, const GLenum& theType) : path(thePath), type(theType) {}

	const string& getPath() const { return path; }
	const GLenum& getType() const { return type; }

private:
	string path;
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

	void setObjectToClip(const mat4& matrix) const { setUniformMat4("objectToClip", matrix); }
	void setObjectToWorld(const mat4& matrix) const { setUniformMat4("objectToWorld", matrix); }
	void setWorldToView(const mat4& matrix) const { setUniformMat4("worldToView", matrix); }
	void setViewToClip(const mat4& matrix) const { setUniformMat4("viewToClip", matrix); }

	void setTextureId(const GLuint& id) const;

	void setMaterialProperty(const PhongProperty& materialProperty) const;
	void setLightProperty(const PhongProperty&	lightProperty, const vec4& position, const int& indexInArray) const;
	void setLightPosition(const vec4& position, const int& indexInArray) const;

	void setTerrainContentData(const TerrainContentData& contentData) const;

	void setUniformGLint(const string& variable, const GLint& value) const;
    void setUniformGLfloat(const string& variable, const GLfloat& value) const;
    void setUniformMat4(const string& variable, const mat4& value) const;
	void setUniformVec3(const string& variable, const vec3& value) const;
    void setUniformVec4(const string& variable, const vec4& value) const;

	void setTransformFeedbackOutput(const vector<string>& varyings) const;
private:
    GLuint programLocation;
};
