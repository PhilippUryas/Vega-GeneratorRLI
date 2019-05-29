#include "rkrimagehandler.h"
#include "rrliimagehandler.h"
#include "srliimagehandler.h"

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
            SRLIImageHandler *srli = new SRLIImageHandler(imageParams);
            return srli;
        }

        case RRLI: {
            RRLIImageHandler *rrli = new RRLIImageHandler(imageParams);
            return rrli;
        }

    }
}


void ImageHandler::rgbToGrayScale() {

    for (int row = 0; row < _image.width(); row++) {
        for (int col = 0; col < _image.height(); col++)
        {
            QColor clrCurrent(_image.pixel(row, col));

            QRgb grayScaleColor;
            int grayScale = 0.299*clrCurrent.red()
                    + 0.587*clrCurrent.green() + 0.114*clrCurrent.blue();
            grayScaleColor = qRgb(grayScale, grayScale, grayScale);

            _image.setPixel(row, col, grayScaleColor);
        }
    }
}
//void ImageHandler::rgbToGrayScale() {}

//void ImageHandler::toPolar() {}

ushort ImageHandler::setUshortPixelFormat(ushort value) {
    return (value / 255.f) * std::numeric_limits<unsigned short>::max();
}

uint ImageHandler::setUintPixelFormat(uint value) {
    return (value / 255.f) * std::numeric_limits<unsigned int>::max();
}

float ImageHandler::setFloatPixelFormat(float value) {
    return (value / 255.f) * std::numeric_limits<float>::max();
}


