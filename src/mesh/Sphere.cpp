#include "mesh/Sphere.h"

using namespace glm;
using namespace std;


Sphere::Sphere() : AbstractMesh() {
	prepareBufferData();
	buildVAO();
}

void Sphere::prepareBufferData() {
	const int NumTimesToSubdivide = 5;
	const int NumTriangles = 4096;  // (4 faces)^(NumTimesToSubdivide + 1)
	int numberOfVertices = 3 * NumTriangles;

	vertices.reserve(numberOfVertices);
	colors.reserve(numberOfVertices);
	normals.reserve(numberOfVertices);

	tetrahedron(NumTimesToSubdivide);
}

void Sphere::triangle(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c) {
    normals.push_back(vec3(a.x, a.y, a.z));
	vertices.push_back(a);
	colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

	normals.push_back(vec3(b.x, b.y, b.z));
	vertices.push_back(b);
	colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

	normals.push_back(vec3(c.x, c.y, c.z));
	vertices.push_back(c);
	colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec4 Sphere::unit(const glm::vec4& p) const {
    float len = p.x * p.x + p.y * p.y + p.z * p.z;
    
    glm::vec4 t;
    if (len > divideByZeroTolerance) {
		t = p / sqrt(len);
		t.w = 1.0;
    }

    return t;
}

void Sphere::divideTriangle(const glm::vec4& a, const glm::vec4& b,  const glm::vec4& c, const int count) {
    if (count > 0) {
        glm::vec4 v1 = unit(a + b);
        glm::vec4 v2 = unit(a + c);
        glm::vec4 v3 = unit(b + c);
        divideTriangle(a, v1, v2, count - 1);
        divideTriangle(c, v2, v3, count - 1);
        divideTriangle(b, v3, v1, count - 1);
        divideTriangle(v1, v3, v2, count - 1);
    } else {
        triangle( a, b, c );
    }
}

void Sphere::tetrahedron(const int count) {
    glm::vec4 v[4] = {
		glm::vec4( 0.0, 0.0, 1.0, 1.0 ),
		glm::vec4( 0.0, 0.942809, -0.333333, 1.0 ),
		glm::vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
		glm::vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };

    divideTriangle(v[0], v[1], v[2], count);
    divideTriangle(v[3], v[2], v[1], count);
    divideTriangle(v[0], v[3], v[1], count);
    divideTriangle(v[0], v[2], v[3], count);
}
