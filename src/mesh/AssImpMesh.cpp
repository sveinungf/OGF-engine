#include "mesh/AssImpMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream> 
#include <glm/gtc/swizzle.hpp>

using namespace glm;
using namespace std;


AssImpMesh::AssImpMesh(aiMesh* mesh) : AbstractMesh() {
	this->id = ++AbstractMesh::count;
	std::cout << "id( " << id << " )";
	unsigned int numberOfVertices = mesh->mNumVertices;

	std::cout << " vertices( " << numberOfVertices << " )";

	vertices.reserve(numberOfVertices);

	for (unsigned int i = 0; i < numberOfVertices; ++i){
		auto v = mesh->mVertices[i];
		vertices.push_back(vec4(v.x, v.y, v.z, 1.0f));

		if (v.x > positiveExtent.x) {
			positiveExtent.x = v.x;
		} else if (v.x < negativeExtent.x) {
			negativeExtent.x = v.x;
		}

		if (v.y > positiveExtent.y) {
			positiveExtent.y = v.y;
		} else if (v.y < negativeExtent.y) {
			negativeExtent.y = v.y;
		}

		if (v.z > positiveExtent.z) {
			positiveExtent.z = v.z;
		} else if (v.z < negativeExtent.z) {
			negativeExtent.z = v.z;
		}
	}

	if (mesh->HasTangentsAndBitangents()){
		std::cout << " tanAndBitan";
	}

	if (mesh->HasNormals()){
		std::cout << " normals";
		normals.reserve(numberOfVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++){
			auto n = mesh->mNormals[i];
			normals.push_back(vec3(n.x, n.y, n.z));
		}
	}

	for (unsigned int uvChanIndex = 0; uvChanIndex < mesh->GetNumUVChannels(); uvChanIndex++){
		if (uvChanIndex == 0 && mesh->HasTextureCoords(uvChanIndex)){
			std::cout << " UVcoords";
			texCoords.reserve(numberOfVertices);
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++){
				auto t = mesh->mTextureCoords[uvChanIndex][i];
				texCoords.push_back(vec2(t.x, t.y));
			}

			computeTangentAndBitangetValues(numberOfVertices);
			std::cout << " gen( tangent bitangent )";
		}
		else break;
	}

	for (unsigned int vColorIndex = 0; vColorIndex < mesh->GetNumColorChannels(); vColorIndex++){
		if (vColorIndex == 0 && mesh->HasVertexColors(vColorIndex)) {
			std::cout << " colors";
			colors.reserve(numberOfVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				auto c = mesh->mColors[vColorIndex][i];
				colors.push_back(vec4(c.r, c.g, c.b, c.a));
			}
		}
		else break;
	}

	std::cout << std::endl;

	buildVAO();
}

void AssImpMesh::computeTangentAndBitangetValues(const unsigned int numberOfVertices) {
	tangents = vector<vec3>(numberOfVertices);
	bitangents = vector<vec3>(numberOfVertices);

	for (unsigned int i = 0; i < numberOfVertices; i += 3) {
		//find triangle corners cornerOne,cornerTwo & cornerThree
		glm::vec4 & vertexCornerOne = vertices[i + 0];
		glm::vec4 & vertexCornerTwo = vertices[i + 1];
		glm::vec4 & vertexCornerThree = vertices[i + 2];

		glm::vec2 & uvCornerOne = texCoords[i + 0];
		glm::vec2 & uvCornerTwo = texCoords[i + 1];
		glm::vec2 & uvCornerThree = texCoords[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = glm::vec3(vertexCornerTwo) - glm::vec3(vertexCornerOne);
		glm::vec3 deltaPos2 = glm::vec3(vertexCornerThree) - glm::vec3(vertexCornerOne);

		// UV delta
		glm::vec2 deltaUV1 = uvCornerTwo - uvCornerOne;
		glm::vec2 deltaUV2 = uvCornerThree - uvCornerOne;

		//WTF is r?
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		// Set the same tangent and bitangent for all three vertices of the triangle.
		tangents[i + 0] = tangent;
		tangents[i + 1] = tangent;
		tangents[i + 2] = tangent;
		bitangents[i + 0] = bitangent;
		bitangents[i + 1] = bitangent;
		bitangents[i + 2] = bitangent;
	}
}
