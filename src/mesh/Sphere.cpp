#include "mesh/Sphere.h"


Sphere::Sphere() : AbstractMesh() {
	prepareBufferData();
	buildVAO();
}

void Sphere::prepareBufferData() {
	const int NumTimesToSubdivide = 5;
	const int NumTriangles        = 4096;  // (4 faces)^(NumTimesToSubdivide + 1)
	numberOfVertices              = 3 * NumTriangles;

	index = 0;
	vertices = new glm::vec4[numberOfVertices];
	bytesOfVertices = sizeof(glm::vec4) * numberOfVertices;
	colors = new glm::vec4[numberOfVertices];
	bytesOfColors = sizeof(glm::vec4) * numberOfVertices;
	normals = new glm::vec3[numberOfVertices];
	bytesOfNormals = sizeof(glm::vec3) * numberOfVertices;
	texCoords = 0;
	bytesOfTexCoords = 0;

	tetrahedron( NumTimesToSubdivide );
	}

void Sphere::tetrahedron( int count )
{
    glm::vec4 v[4] = {
	glm::vec4( 0.0, 0.0, 1.0, 1.0 ),
	glm::vec4( 0.0, 0.942809, -0.333333, 1.0 ),
	glm::vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
	glm::vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };

    divideTriangle( v[0], v[1], v[2], count );
    divideTriangle( v[3], v[2], v[1], count );
    divideTriangle( v[0], v[3], v[1], count );
    divideTriangle( v[0], v[2], v[3], count );
}

void Sphere::triangle( const glm::vec4& a, const glm::vec4& b, const glm::vec4& c )
{
    normals[index] = glm::vec3(a.x, a.y, a.z); vertices[index] = a; colors[index] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); index++;
	normals[index] = glm::vec3(b.x, b.y, b.z); vertices[index] = b; colors[index] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); index++;
	normals[index] = glm::vec3(c.x, c.y, c.z); vertices[index] = c; colors[index] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); index++;
}

glm::vec4 Sphere::unit( const glm::vec4& p )
{
    float len = p.x*p.x + p.y*p.y + p.z*p.z;
    
    glm::vec4 t;
    if ( len > divideByZeroTolerance ) {
	t = p / sqrt(len);
	t.w = 1.0;
    }

    return t;
}

void Sphere::divideTriangle( const glm::vec4& a, const glm::vec4& b,  const glm::vec4& c, int count )
{
    if ( count > 0 ) {
        glm::vec4 v1 = unit( a + b );
        glm::vec4 v2 = unit( a + c );
        glm::vec4 v3 = unit( b + c );
        divideTriangle(  a, v1, v2, count - 1 );
        divideTriangle(  c, v2, v3, count - 1 );
        divideTriangle(  b, v3, v1, count - 1 );
        divideTriangle( v1, v3, v2, count - 1 );
    }
    else {
        triangle( a, b, c );
    }
}
