#include "ShaderProgram.h"

using namespace glm;
using namespace std;


ShaderProgram& ShaderProgram::operator<<(const GLenum type){
	if (type == Shader::LINK) {
		glLinkProgram(programLocation);

		GLint linked;
		glGetProgramiv(programLocation, GL_LINK_STATUS, &linked);

		if (!linked) {
			std::cerr << "Shader program failed to link" << std::endl;
			GLint  logSize;
			glGetProgramiv(programLocation, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(programLocation, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			throw std::runtime_error("Failed to link shader");
		}
		std::cout << "  Shader linked!" << std::endl << std::endl;
	}

	return *this;
}

ShaderProgram& ShaderProgram::operator<<(const Shader& s) {
	{
		switch (s.getType()){
		case Shader::FRAG:
			std::cout << "  Fragment: ";
			break;
		case Shader::GEOM:
			std::cout << "  Geometry: ";
			break;
		case Shader::VERT:
			std::cout << "  Vertex:   ";
			break;
		}
		std::cout << s.getPath() << std::endl;
	}

	ifstream fileStream(s.getPath());

	if (fileStream.fail()) {
		std::cerr << "Can't open file " << s.getPath() << std::endl;
		throw std::runtime_error("Can't open file " + s.getPath());
	}

	stringstream buffer;
	buffer << fileStream.rdbuf();

	string fileString = buffer.str();
	const GLchar* fileCharArray = fileString.c_str();

	GLuint shader = glCreateShader(s.getType());
	glShaderSource(shader, 1, &fileCharArray, NULL);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		std::cerr << s.getPath() << " failed to compile:" << std::endl;
		GLint  logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetShaderInfoLog(shader, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		throw std::runtime_error("Failed to compile shader");
	}

	glAttachShader(programLocation, shader);

	return *this;
}

void ShaderProgram::setTextureId(const GLuint id) const {
	stringstream ss;
	ss << "texArray[" << id << "]";
	setUniformGLint(ss.str(), id);
}

void ShaderProgram::setMaterialProperty(const PhongProperty&
                                        materialProperty) const {
    setUniformVec4("material.ambient", materialProperty.getAmbient());
    setUniformVec4("material.diffuse", materialProperty.getDiffuse());
    setUniformVec4("material.specular", materialProperty.getSpecular());
    setUniformGLfloat("material.shininess", materialProperty.getShininess());
}

void ShaderProgram::setLightProperty(const PhongProperty& lightProperty, const glm::vec4& position, const int& indexInArray) const {
	stringstream lightAmbient;  /**/  lightAmbient << "light[" << indexInArray << "].ambient";
	stringstream lightDiffuse;  /**/  lightDiffuse << "light[" << indexInArray << "].diffuse";
	stringstream lightSpecular; /**/  lightSpecular << "light[" << indexInArray << "].specular";
	stringstream lightPosition; /**/  lightPosition << "light[" << indexInArray << "].position";
	ShaderProgram::setUniformVec4(lightAmbient.str(), lightProperty.getAmbient());
	ShaderProgram::setUniformVec4(lightDiffuse.str(), lightProperty.getDiffuse());
	ShaderProgram::setUniformVec4(lightSpecular.str(), lightProperty.getSpecular());
	ShaderProgram::setUniformVec4(lightPosition.str(), position);
}

void ShaderProgram::setLightPosition(const glm::vec4& position, const int& indexInArray) const {
	stringstream lightPosition; lightPosition << "light[" << indexInArray << "].position";
	ShaderProgram::setUniformVec4(lightPosition.str(), position);
}

void ShaderProgram::setTerrainContentData(const TerrainContentData& contentData) const {
	setUniformGLfloat("rockHeight", contentData.getRockHeight());
	setUniformGLfloat("snowHeight", contentData.getSnowHeight());
	setUniformGLfloat("waterHeight", contentData.getWaterHeight());
	setUniformGLfloat("mixRange", TerrainContentData::TEXTURE_MIX_RANGE);
}

void ShaderProgram::setUniformGLint(const string& variable,
	const GLint value) const {
	glUseProgram(programLocation);
	GLuint uniformLocation = glGetUniformLocation(programLocation,
		variable.c_str());
	glUniform1i(uniformLocation, value);
}

void ShaderProgram::setUniformGLfloat(const string& variable,
                                      const GLfloat value) const {
	glUseProgram(programLocation);
    GLuint uniformLocation = glGetUniformLocation(programLocation,
                             variable.c_str());
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::setUniformMat4(const string& variable,
                                   const mat4& value) const {
	glUseProgram(programLocation);
    GLuint uniformLocation = glGetUniformLocation(programLocation,
                             variable.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setUniformVec3(const string& variable,
                                   const vec3& value) const {
	glUseProgram(programLocation);
    GLuint uniformLocation = glGetUniformLocation(programLocation,
                             variable.c_str());
    glUniform3fv(uniformLocation, 1, &value[0]);
}

void ShaderProgram::setUniformVec4(const string& variable,
                                   const vec4& value) const {
	glUseProgram(programLocation);
    GLuint uniformLocation = glGetUniformLocation(programLocation,
                             variable.c_str());
    glUniform4fv(uniformLocation, 1, &value[0]);
}

void ShaderProgram::setTransformFeedbackOutput(const vector<string>& varyings) const {
	// The tedious process of getting a GLchar** from a vector<string>
	unsigned int size = varyings.size();
	const GLchar** arr = new const GLchar*[size];

	for (unsigned int i = 0; i < size; ++i) {
		arr[i] = varyings[i].c_str();
	}

	// Tells the transform feedback what shader variables to monitor
	glTransformFeedbackVaryings(programLocation, size, arr, GL_SEPARATE_ATTRIBS);

	delete[] arr;
}
