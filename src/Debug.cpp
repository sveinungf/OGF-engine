#include "Debug.h"


void checkErrorAndStop(const string& errString, bool stop) {
    GLenum errCode = glGetError();

    if (errCode != GL_NO_ERROR) {
        stringstream ss;
        ss << "err " << errString << ": " << gluErrorString(errCode);

		cerr << ss.str() << endl;

        if (stop) {
            throw runtime_error(ss.str());
        }
    }
}

string hyphenPaddedMessage(const string& message, int length) {
	stringstream ss;
	int messageLength = message.length();
	int paddingLength = length - messageLength;

	if (paddingLength > 0) {
		int firstHalf = paddingLength / 2;
		int secondHalf = paddingLength - firstHalf;

		ss << setfill('-') << setw(firstHalf) << "" << message << setw(secondHalf) << "";
	} else {
		ss << message;
	}

	return ss.str();
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei /*length*/, const GLchar* message, void* /*userParam*/) {

	cerr << endl << hyphenPaddedMessage("openglDebugCallback START") << endl;
	cerr << "message: " << message << endl;
	cerr << "source: ";

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		cerr << "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		cerr << "WINDOW_SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		cerr << "SHADER_COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		cerr << "THIRD_PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		cerr << "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		cerr << "OTHER";
		break;
	default:
		cerr << "UNKNOWN";
		break;
	}

	cerr << endl << "type: ";

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cerr << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cerr << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cerr << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cerr << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cerr << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_MARKER:
		cerr << "MARKER";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		cerr << "PUSH_GROUP";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		cerr << "POP_GROUP";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cerr << "OTHER";
		break;
	default:
		cerr << "UNKNOWN";
		break;
	}

	cerr << endl << "id: " << id << endl;
	cerr << "severity: ";

	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		cerr << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cerr << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cerr << "HIGH";
		break;
	default:
		cerr << "UNKNOWN";
		break;
	}

	cerr << endl << hyphenPaddedMessage("openglDebugCallback END") << endl << endl;
}

void glfwErrorCallback(int error, const char* description) {
	cerr << endl << hyphenPaddedMessage("glfwErrorCallback START") << endl;
	cerr << "error: " << error << endl;
	cerr << "description: " << description << endl;
	cerr << hyphenPaddedMessage("glfwErrorCallback END") << endl << endl;
}
