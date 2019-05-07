#include "rkrimagehandler.h"

ImageHandler::ImageHandler(ImageParams& imageParams) {
    QImage image(imageParams.sourceImagePath);

    _image = image;
    _imageParams = &imageParams;
}

ImageHandler::~ImageHandler(){}

ImageHandler* ImageHandler::create(ImageParams& imageParams) {
    switch(imageParams.imageType) {
        case RKR: {
            RKRImageHandler *rkr = new RKRImageHandler(imageParams);
            return rkr;
        }

        case SRLI: {
            //return *srli
            return NULL;
        }

        case RRLI: {
            //return *rrli
            return NULL;
        }

    }
}

ushort ImageHandler::setUshortPixelFormat(ushort value) {
    return (value / 255.f) * std::numeric_limits<unsigned short>::max();
   // _image.pixel(x, y) / 255.0 * std::numeric_limits<unsigned short>::max()
}

uint ImageHandler::setUintPixelFormat(uint value) {
    return (value / 255.f) * std::numeric_limits<unsigned int>::max();
}


