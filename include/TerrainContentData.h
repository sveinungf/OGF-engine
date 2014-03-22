#pragma once

#include <vector>
#include <glmhppnowarnings.h>


class TerrainContentData {

public:
	static const float MAX_HEIGHT_DIFFERENCE;
	static const float WATER_HEIGHT_PERCENT;
	static const float ROCK_HEIGHT_PERCENT;
	static const float SNOW_HEIGHT_PERCENT;
	static const float TEXTURE_MIX_RANGE;

	TerrainContentData() : rockHeight(0.0f), snowHeight(0.0f), waterHeight(0.0f) {}

	float getRockHeight() const { return rockHeight; }
	float getSnowHeight() const { return snowHeight; }
	float getWaterHeight() const { return waterHeight; }
	void setRockHeight(float height) { rockHeight = height; }
	void setSnowHeight(float height) { snowHeight = height; }
	void setWaterHeight(float height) { waterHeight = height; }

	const std::vector<glm::vec3>& getTreePositions() { return treePositions; }
	void setTreePositions(const std::vector<glm::vec3>& vector) { treePositions = vector; }
	const std::vector<glm::vec3>& getGrassPositions() { return grassPositions; }
	void setGrassPositions(const std::vector<glm::vec3>& vector) { grassPositions = vector; }
	const std::vector<glm::vec3>& getGrassNormals() { return grassNormals; }
	void setGrassNormals(const std::vector<glm::vec3>& vector) { grassNormals = vector; }

private:
	float rockHeight;
	float snowHeight;
	float waterHeight;
	std::vector<glm::vec3> treePositions;
	std::vector<glm::vec3> grassPositions;
	std::vector<glm::vec3> grassNormals;
};
