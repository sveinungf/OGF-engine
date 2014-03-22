#pragma once

#include <string>
#include <SOIL.h>
#include "../Image.h"
#include "../TerrainContentData.h"
#include "AbstractMesh.h"


class Terrain : public AbstractMesh {

public:
	explicit Terrain(const std::string& filename);
	virtual ~Terrain() override;

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
