#include "Image.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SOIL.h>

using namespace std;


Image::Image(const string& filename, const Format format) : channels(0), height(0), width(0), pixelDataLength(0), pixelData(nullptr) {
	ifstream ifile(filename);

	if (ifile.good()) {
		// SOIL loads images with Y-axis flipped
		unsigned char* flippedPixelData = SOIL_load_image(filename.c_str(), &width, &height, &channels, format);
		pixelDataLength = width * height * format;
		
		pixelData = new unsigned char[pixelDataLength];

		// Flip the Y-axis
		for (int i = 0; i < height; ++i) {
			copy(flippedPixelData + i * width * format, flippedPixelData + i * width * format + width * format, pixelData + (height - 1 - i) * width * format);
		}
	} else {
		stringstream ss;
		ss << "Could not open file: " << filename;
		cerr << ss.str() << endl;
		throw runtime_error(ss.str());
	}
}

Image::Image(const Image& other) : channels(other.channels), height(other.height), width(other.width), pixelDataLength(other.pixelDataLength), pixelData(pixelDataLength ? new unsigned char[pixelDataLength] : nullptr) {
	std::copy(other.pixelData, other.pixelData + pixelDataLength, pixelData);
}

Image::Image(Image&& other) : channels(0), height(0), width(0), pixelDataLength(0), pixelData(nullptr) {
	swap(*this, other);
}

Image::~Image() {
    delete [] pixelData;
}

Image& Image::operator=(Image other) {
    swap(*this, other);
    return *this;
} 

void swap(Image& first, Image& second) {
	// Enable ADL
    using std::swap; 

	swap(first.channels, second.channels);
	swap(first.height, second.height);
	swap(first.width, second.width);
	swap(first.pixelDataLength, second.pixelDataLength);
	swap(first.pixelData, second.pixelData);
}
