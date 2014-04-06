#ifndef GLMHPPNOWARNINGS_H_
#define GLMHPPNOWARNINGS_H_

#if defined(__GNUC__) || defined(__GNUG__)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wpedantic" // Anonymous structs in glm
#	include <glm/glm.hpp>
#	include <glm/ext.hpp>
#	pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable:4201) // Nameless structs in glm
#	include <glm/glm.hpp>
#	include <glm/ext.hpp>
#	pragma warning(pop)
#else
#	include <glm/glm.hpp>
#	include <glm/ext.hpp>
#endif

#endif /* GLMHPPNOWARNINGS_H_ */
