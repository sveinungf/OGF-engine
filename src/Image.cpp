#include "Image.h"

using namespace std;


Image::Image(const string& filename, const Format& format) : channels(0), height(0), width(0), pixelData(nullptr) {
	ifstream ifile(filename);

	if (ifile.good()) {
		unsigned char* flippedPixelData = SOIL_load_image(filename.c_str(), &width, &height, &channels, format);

		// SOIL loads images with Y-axis flipped
		pixelData = new unsigned char[width * height * format];

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

Image::~Image() {
    delete pixelData;
}
