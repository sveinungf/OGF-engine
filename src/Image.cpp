#include "Image.h"


Image::Image(const string& filename, const Format& format) {
    pixelData = SOIL_load_image(filename.c_str(), &width, &height, &channels,
                                format);
}

Image::~Image() {
    delete pixelData;
}
