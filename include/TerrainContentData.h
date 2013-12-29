#pragma once

#include <vector>
#include <glmhppnowarnings.h>

using namespace glm;
using namespace std;


class TerrainContentData {

public:
	static const float MAX_HEIGHT_DIFFERENCE;
	static const float WATER_HEIGHT_PERCENT;
	static const float ROCK_HEIGHT_PERCENT;
	static const float SNOW_HEIGHT_PERCENT;
	static const float TEXTURE_MIX_RANGE;

	TerrainContentData() {};

	float getRockHeight() const { return rockHeight; }
	float getSnowHeight() const { return snowHeight; }
	float getWaterHeight() const { return waterHeight; }
	void setRockHeight(float height) { rockHeight = height; }
	void setSnowHeight(float height) { snowHeight = height; }
	void setWaterHeight(float height) { waterHeight = height; }

	const vector<vec3>& getTreePositions() { return treePositions; }
	void setTreePositions(const vector<vec3>& vector) { treePositions = vector; }
	const vector<vec3>& getGrassPositions() { return grassPositions; }
	void setGrassPositions(const vector<vec3>& vector) { grassPositions = vector; }
	const vector<vec3>& getGrassNormals() { return grassNormals; }
	void setGrassNormals(const vector<vec3>& vector) { grassNormals = vector; }

private:
	float rockHeight;
	float snowHeight;
	float waterHeight;
	vector<vec3> treePositions;
	vector<vec3> grassPositions;
	vector<vec3> grassNormals;
};
