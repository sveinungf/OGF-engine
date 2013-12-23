#include "mesh/AssImpMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream> 
#include <glm/gtc/swizzle.hpp>


AssImpMesh::AssImpMesh(aiMesh* mesh){
	this->id = ++AbstractMesh::count;
	std::cout << "id( " << id << " )";
	numberOfVertices = mesh->mNumVertices;

	std::cout << " vertices( " << numberOfVertices << " )";

	bytesOfVertices = sizeof(glm::vec4) * numberOfVertices;

	vertices = new glm::vec4[numberOfVertices];


	for (unsigned int i = 0; i < mesh->mNumVertices; i++){
		auto v = mesh->mVertices[i];
		vertices[i] = glm::vec4(v.x, v.y, v.z, 1.0f);

		if (v.x > positiveExtent.x) {
			positiveExtent.x = v.x;
		}

		if (v.x < negativeExtent.x) {
			negativeExtent.x = -v.x;
		}

		if (v.y > positiveExtent.y) {
			positiveExtent.y = v.y;
		}

		if (v.y < negativeExtent.y) {
			negativeExtent.y = -v.y;
		}

		if (v.z > positiveExtent.z) {
			positiveExtent.z = v.z;
		}

		if (v.z < negativeExtent.z) {
			negativeExtent.z = -v.z;
		}
	}

	if (mesh->HasTangentsAndBitangents()){
		std::cout << " tanAndBitan";
	}

	if (mesh->HasNormals()){
		std::cout << " normals";
		bytesOfNormals = sizeof(glm::vec3) * numberOfVertices;
		normals = new glm::vec3[numberOfVertices];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++){
			auto n = mesh->mNormals[i];
			normals[i] = glm::vec3(n.x, n.y, n.z);
		}
	}

	for (unsigned int uvChanIndex = 0; uvChanIndex < mesh->GetNumUVChannels(); uvChanIndex++){
		if (uvChanIndex == 0 && mesh->HasTextureCoords(uvChanIndex)){
			std::cout << " UVcoords";
			bytesOfTexCoords = sizeof(glm::vec2) * numberOfVertices;
			texCoords = new glm::vec2[numberOfVertices];
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++){
				auto t = mesh->mTextureCoords[uvChanIndex][i];
				texCoords[i] = glm::vec2(t.x, t.y);
			}

			computeTangentAndBitangetValues();
			std::cout << " gen( tangent bitangent )";
		}
		else break;
	}

	for (unsigned int vColorIndex = 0; vColorIndex < mesh->GetNumColorChannels(); vColorIndex++){
		if (vColorIndex == 0 && mesh->HasVertexColors(vColorIndex)){
			std::cout << " colors";
			bytesOfColors = sizeof(glm::vec3) * numberOfVertices;
			colors = new glm::vec4[numberOfVertices];
			for (unsigned int i = 0; i < mesh->mNumVertices; i++){
				auto c = mesh->mColors[vColorIndex][i];
				colors[i] = glm::vec4(c.r, c.g, c.b, c.a);
			}
		}
		else break;
	}

	std::cout << std::endl;

	buildVAO();
}

void AssImpMesh::computeTangentAndBitangetValues() {
	//Create arrays
	tangents = new glm::vec3[numberOfVertices];
	bytesOfTangents = sizeof(glm::vec3) * numberOfVertices;
	bitangents = new glm::vec3[numberOfVertices];
	bytesOfBitangents = sizeof(glm::vec3) * numberOfVertices;

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
		tangents[i + 0] = tangent;  tangents[i + 1] = tangent;  tangents[i + 2] = tangent;
		bitangents[i + 0] = bitangent;  bitangents[i + 0] = bitangent;  bitangents[i + 0] = bitangent;
	}
}
