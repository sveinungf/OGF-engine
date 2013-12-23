#pragma once

#include <string>
#pragma warning(push)
#pragma warning(disable:4201) // nameless structs
#include <glm\ext.hpp>
#pragma warning(pop)
#include <SOIL.h>
#include "../Image.h"
#include "../TerrainContentData.h"
#include "AbstractMesh.h"

using namespace glm;
using namespace std;


class Terrain : public AbstractMesh {

public:
	Terrain(const string& filename);
	~Terrain();

	Image* getHeightmap() const { return heightmap; }
	int getLength() const { return length; }
	int getWidth() const { return width; }
	float getMinHeight() const { return minHeight; }
	float getMaxHeight() const { return maxHeight; }
	const TerrainContentData& getContentData() const { return contentData; }

	float getHeightAt(int x, int z) const;
	const glm::vec3& getPointAt(int x, int z) const;
	const glm::vec3& getNormalAt(int x, int z) const;

private:
	Image* heightmap;
	int length;
	int width;

	float minHeight;
	float maxHeight;

	TerrainContentData contentData;

	glm::vec3* points;
	glm::vec3* pointNormals;

	virtual void prepareBufferData() override;
	void populateContentData();
};
