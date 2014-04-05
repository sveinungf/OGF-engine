#pragma once

#include <string>
#include <GL/glew.h>


class Shader {

public:
	enum ShaderType {
		FRAGMENT = GL_FRAGMENT_SHADER,
		VERTEX = GL_VERTEX_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER
	};

	explicit Shader(const std::string& thePath, const ShaderType theType) : path(thePath), type(theType) {}

	const std::string& getPath() const { return path; }
	const ShaderType getType() const { return type; }

private:
	std::string path;
	ShaderType type;
};
