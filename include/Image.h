#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <SOIL.h>


class Image {

public:
	enum Format { GREYSCALE = 1, RGB = 3, RGBA = 4 };

	Image(const std::string& filename, const Format& format);
	~Image();

	int getChannels() const { return channels; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	unsigned char* getPixelData() const { return pixelData; }

private:
    int channels;
    int height;
    int width;
    unsigned char* pixelData;
};
