#pragma once

#include <string>


class Image {

public:
	enum Format { GREYSCALE = 1, RGB = 3, RGBA = 4 };

	Image() : channels(0), height(0), width(0), pixelDataLength(0), pixelData(nullptr) {}
	explicit Image(const std::string& filename, const Format format);
	Image(const Image& other);
	Image(Image&& other);
	~Image();

	int getChannels() const { return channels; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	unsigned char* getPixelData() const { return pixelData; }

	Image& operator=(Image other); // Parameter must be value type (copy-and-swap)

	friend void swap(Image& first, Image& second); // nothrow

private:
    int channels;
    int height;
    int width;
    size_t pixelDataLength;
	unsigned char* pixelData;
};
