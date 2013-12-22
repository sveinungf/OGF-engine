#include "mesh/Terrain.h"


Terrain::Terrain(const string& filename) : AbstractMesh() {
	heightmap = new Image(filename, Image::GREYSCALE);
	
	prepareBufferData();
	populateContentData();
	buildVAO();
}

Terrain::~Terrain() {
	delete heightmap;
	delete points;
	delete pointNormals;
}

void Terrain::prepareBufferData() {
	float heightFactor = TerrainContentData::MAX_HEIGHT_DIFFERENCE / 255.0f;

	unsigned char* imageData = heightmap->getPixelData();
	length = heightmap->getHeight();
	width = heightmap->getWidth();

	// Just for pure performance
	int lastLengthIndex = length - 1;
	int lastWidthIndex = width - 1;

	numberOfVertices = lastWidthIndex * lastLengthIndex * 6;

    vertices = new glm::vec4[numberOfVertices];
	normals = new glm::vec3[numberOfVertices];
	texCoords = new glm::vec2[numberOfVertices];

	bytesOfVertices = (sizeof glm::vec4) * numberOfVertices;
	bytesOfNormals = (sizeof glm::vec3) * numberOfVertices;
	bytesOfColors = 0;
	bytesOfTexCoords = (sizeof glm::vec2) * numberOfVertices;

    int size = width * length;
    points = new glm::vec3[size];
	pointNormals = new glm::vec3[size];
	
	unsigned char minByteHeight = imageData[0];
	unsigned char maxByteHeight = minByteHeight;

	// Find lowest and highest points in the heightmap
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
			unsigned char current = imageData[i * width + j];

			if (current < minByteHeight) {
				minByteHeight = current;
			} else if (current > maxByteHeight) {
				maxByteHeight = current;
			}
        }
    }

	// Byte value of what will be at height 0 in the terrain
	float byteHeightZero = (maxByteHeight - minByteHeight) * TerrainContentData::WATER_HEIGHT_PERCENT + minByteHeight;

	minHeight = (minByteHeight - byteHeightZero) * heightFactor;
	maxHeight = (maxByteHeight - byteHeightZero) * heightFactor;

    float startX = width / 2.0f;
    float startZ = length / 2.0f;

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = i * width + j;
            float x = startX - j;
			float y = (imageData[index] - byteHeightZero) * heightFactor;
            float z = startZ - i;
            points[index] = glm::vec3(x, y, z);
        }
    }

	// Normal calculations
	for (int i = 1; i < lastLengthIndex; ++i) {
        for (int j = 1; j < lastWidthIndex; ++j) {
			int pastRow = (i - 1) * width + j;
			int current = i * width + j;
			int nextRow = (i + 1) * width + j;

			/*
			6_______7_______8	-> j++
			|\      |      /|
			| \  F  |  G  / |	// Vertex 0 is the current vertex. The surrounding vertices is numbered clockwise.
			|  \    |    /  |	// The surrounding quads is named from A-H, also clockwise.
			|   \   |   /   |
			|    \  |  /    |	// The normal for the current vertex will be calculated by using the normals of the surrounding triangles.
			|  E  \ | /  H  |	// The triangle normals will be summed, and then normalized, to find the current vertex normal.
			5______\0/______1
			|      /|\      |
			|  D  / | \  A  |
			|    /  |  \    |
			|   /   |   \   |
			|  /    |    \  |
			| /  C  |  B  \ |
			4/______3______\2

			|
			v
			i++

			*/

            glm::vec3 vertex0 = points[current];
            glm::vec3 vertex1 = points[current + 1];
			glm::vec3 vertex2 = points[nextRow + 1];
			glm::vec3 vertex3 = points[nextRow];
			glm::vec3 vertex4 = points[nextRow - 1];
			glm::vec3 vertex5 = points[current - 1];
			glm::vec3 vertex6 = points[pastRow - 1];
			glm::vec3 vertex7 = points[pastRow];
			glm::vec3 vertex8 = points[pastRow + 1];

			glm::vec3 vector01 = vertex1 - vertex0;	// Vector from vertex 0 to vertex 1
			glm::vec3 vector02 = vertex2 - vertex0; // Vector from vertex 0 to vertex 2
			glm::vec3 vector03 = vertex3 - vertex0; // Vector from vertex 0 to vertex 3
			glm::vec3 vector04 = vertex4 - vertex0; // Vector from vertex 0 to vertex 4
			glm::vec3 vector05 = vertex5 - vertex0; // Vector from vertex 0 to vertex 5
			glm::vec3 vector06 = vertex6 - vertex0; // Vector from vertex 0 to vertex 6
			glm::vec3 vector07 = vertex7 - vertex0; // Vector from vertex 0 to vertex 7
			glm::vec3 vector08 = vertex8 - vertex0; // Vector from vertex 0 to vertex 8

			// According to the right-hand rule, the resulting vectors from the cross-products will point upwards.
			glm::vec3 normalA = glm::normalize(glm::cross(vector02, vector01));
            glm::vec3 normalB = glm::normalize(glm::cross(vector03, vector02));
            glm::vec3 normalC = glm::normalize(glm::cross(vector04, vector03));
            glm::vec3 normalD = glm::normalize(glm::cross(vector05, vector04));
			glm::vec3 normalE = glm::normalize(glm::cross(vector06, vector05));
			glm::vec3 normalF = glm::normalize(glm::cross(vector07, vector06));
			glm::vec3 normalG = glm::normalize(glm::cross(vector08, vector07));
			glm::vec3 normalH = glm::normalize(glm::cross(vector01, vector08));

			pointNormals[current] = glm::normalize(normalA + normalB + normalC + normalD + normalE + normalF + normalG + normalH);
        }
    }

	// Texture coordinates
	glm::vec2 upperLeft(0.0f, 1.0f);
	glm::vec2 upperRight(1.0f, 1.0f);
	glm::vec2 lowerLeft(0.0f, 0.0f);
	glm::vec2 lowerRight(1.0f, 0.0f);

	int index = 0;

	// Triangles calculations
    for (int i = 0; i < lastLengthIndex; ++i) {
        for (int j = 0; j < lastWidthIndex; ++j) {
			int current = i * width + j;
			int nextRow = ((i + 1) * width) + j;

			/*
			 ________________	-> j++
			|       |       |
			|       |       |	// Vertex 0 is the current vertex. The other vertices is numbered clockwise within the same quad.
			|       |       |
			|       |       |
			|       |       |
			|       |       |
			|_______0_______1
			|       |\      |
			|       | \     |
			|       |  \    |
			|       |   \   |
			|       |    \  |
			|       |     \ |
			|_______3______\2

			|
			v
			i++

			*/

			glm::vec4 vertex0 = glm::vec4(points[current], 1.0f);
			glm::vec4 vertex1 = glm::vec4(points[current + 1], 1.0f);
			glm::vec4 vertex2 = glm::vec4(points[nextRow + 1], 1.0f);
			glm::vec4 vertex3 = glm::vec4(points[nextRow], 1.0f);

			glm::vec3 normal0 = pointNormals[current];
			glm::vec3 normal1 = pointNormals[current + 1];
			glm::vec3 normal2 = pointNormals[nextRow + 1];
			glm::vec3 normal3 = pointNormals[nextRow];

            vertices[index] = vertex0;
			texCoords[index] = upperLeft;
			normals[index] = normal0;
            ++index;

			vertices[index] = vertex2;
			texCoords[index] = lowerRight;
			normals[index] = normal2;
			++index;

            vertices[index] = vertex1;
			texCoords[index] = upperRight;
			normals[index] = normal1;
            ++index;

            vertices[index] = vertex0;
			texCoords[index] = upperLeft;
			normals[index] = normal0;
            ++index;

			vertices[index] = vertex3;
			texCoords[index] = lowerLeft;
			normals[index] = normal3;
			++index;

            vertices[index] = vertex2;
			texCoords[index] = lowerRight;
			normals[index] = normal2;
            ++index;
        }
    }
}

float Terrain::getHeightAt(int x, int z) const {
	return points[x * heightmap->getWidth() + z].y;
}

const glm::vec3& Terrain::getPointAt(int x, int z) const {
	return points[x * heightmap->getWidth() + z];
}

const glm::vec3& Terrain::getNormalAt(int x, int z) const {
	return pointNormals[x * heightmap->getWidth() + z];
}

void Terrain::populateContentData() {
	vector<vec3> treePositions;
	vector<vec3> grassPositions;
	vector<vec3> grassNormals;

	float actualHeightDifference = maxHeight - minHeight;
	float waterHeight = actualHeightDifference * TerrainContentData::WATER_HEIGHT_PERCENT + minHeight; // = 0.0f
	float rockHeight = actualHeightDifference * TerrainContentData::ROCK_HEIGHT_PERCENT + minHeight;
	float snowHeight = actualHeightDifference * TerrainContentData::SNOW_HEIGHT_PERCENT + minHeight;

	contentData.setWaterHeight(waterHeight);
	contentData.setRockHeight(rockHeight);
	contentData.setSnowHeight(snowHeight);

	float maxHeightDifference = 0.0f;

	for (int i = 1; i < length - 1; ++i) {
		for (int j = 1; j < width - 1; ++j) {
			int pastRow = (i - 1) * width + j;
			int current = i * width + j;
			int nextRow = (i + 1) * width + j;

			/*
			6_______7_______8	-> j++
			|       |       |
			|       |       |	// Vertex 0 is the current vertex. The surrounding vertices is numbered clockwise.
			|       |       |
			|       |       |
			|       |       |
			|       |       |
			5_______0_______1
			|       |       |
			|       |       |
			|       |       |
			|       |       |
			|       |       |
			|       |       |
			4_______3_______2

			|
			v
			i++

			*/
			glm::vec3 vertex0 = points[current];
			float height = vertex0.y;

			if (height < rockHeight && height > waterHeight) {
				glm::vec3 surroundingVertices[8];
				surroundingVertices[0] = points[current + 1];
				surroundingVertices[1] = points[nextRow + 1];
				surroundingVertices[2] = points[nextRow];
				surroundingVertices[3] = points[nextRow - 1];
				surroundingVertices[4] = points[current - 1];
				surroundingVertices[5] = points[pastRow - 1];
				surroundingVertices[6] = points[pastRow];
				surroundingVertices[7] = points[pastRow + 1];
				
				bool eligibleForTree = true;

				for (int i = 0; i < 8; ++i) {
					float surroundingHeight = surroundingVertices[i].y;
					float heightDifference = abs(surroundingHeight - height);

					if (heightDifference > maxHeightDifference) {
						eligibleForTree = false;
						break;
					}
				}

				float random = (float) rand() / RAND_MAX; // Random value between 0.0f and 1.0f

				if (eligibleForTree && random < 0.1f) {
					treePositions.push_back(vertex0);
				} else if (random < 0.7f) {
					grassPositions.push_back(vertex0);
					grassNormals.push_back(pointNormals[current]);
				}
			}
		}
	}

	contentData.setTreePositions(treePositions);
	contentData.setGrassPositions(grassPositions);
	contentData.setGrassNormals(grassNormals);
}
