#include "Debug.h"

/*
	@author Endre Oma
*/
void checkErrorAndStop(const std::string& errString, bool stop) {
    GLenum errCode = glGetError();

    if (errCode !=
            GL_NO_ERROR) { //
        //std::cerr << "err " << errString << ": " << gluErrorString(
        //errCode) << std::endl;
        std::stringstream ss;
        ss << "err " << errString << ": " << gluErrorString(errCode);

        if (stop) {
            throw std::runtime_error(ss.str());
        } else {
            std::cerr << ss.str() << std::endl;
        }
    }
}
