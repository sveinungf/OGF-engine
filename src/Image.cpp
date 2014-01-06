#include "Image.h"


Image::Image(const string& filename, const Format& format) {
	unsigned char* flippedPixelData = SOIL_load_image(filename.c_str(), &width, &height, &channels, format);

	// SOIL loads images with Y-axis flipped
	pixelData = new unsigned char[width * height * format];
	for (int i = 0; i < height; ++i) {
		std::copy(flippedPixelData + i * width * format, flippedPixelData + i * width * format + width * format, pixelData + (height - 1 - i) * width * format);
	}
}

Image::~Image() {
    delete pixelData;
}
