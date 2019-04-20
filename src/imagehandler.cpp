#include "imagehandler.h"

ImageHandler::ImageHandler(ImageParams& imageParams) {
    QImage image(imageParams.path);
    _image = image;
    _imageParams = &imageParams;
}

ImageHandler::~ImageHandler(){}

ushort ImageHandler::setUshortPixelFormat(QRgb value) {
    return value / 255.0 * std::numeric_limits<unsigned short>::max();
   // _image.pixel(x, y) / 255.0 * std::numeric_limits<unsigned short>::max()
}

