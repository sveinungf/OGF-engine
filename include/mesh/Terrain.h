#pragma once

#include <string>
#include <SOIL.h>
#include "../Image.h"
#include "../TerrainContentData.h"
#include "AbstractMesh.h"


class Terrain : public AbstractMesh {

public:
	explicit Terrain(const std::string& filename);
	virtual ~Terrain() override {}

	// Virtual constructor idiom
	virtual Terrain* clone() const override { return new Terrain(*this); }

	const Image& getHeightmap() const { return heightmap; }
	int getLength() const { return heightmap.getHeight(); }
	int getWidth() const { return heightmap.getWidth(); }
	float getMinHeight() const { return minHeight; }
	float getMaxHeight() const { return maxHeight; }
	const TerrainContentData& getContentData() const { return contentData; }

	float getHeightAt(int x, int z) const;
	const glm::vec4& getPointAt(int x, int z) const;
	const glm::vec3& getNormalAt(int x, int z) const;

private:
	Image heightmap;

	float minHeight;
	float maxHeight;

	TerrainContentData contentData;

	void prepareBufferData();
	void populateContentData();
};
