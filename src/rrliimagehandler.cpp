#include "rrliimagehandler.h"
#include <QFile>
#include <math.h>

RRLIImageHandler::RRLIImageHandler(ImageParams& imageParams) :
                ImageHandler(imageParams) {}

RRLIImageHandler::~RRLIImageHandler() {}

void RRLIImageHandler::resize() {
    QImage polarImage(_imageParams->targetWidth, _imageParams->targetHeight,
                      QImage::Format_RGB32);

    for(int y = 0; y < _imageParams->targetHeight; y++) {
        for(int x = 0; x < _imageParams->targetWidth; x++) {

                unsigned yi = float(y)/ _imageParams->targetHeight * (_image.height() - 1);
                unsigned xi = float(x)/ _imageParams->targetWidth * (_image.width() - 1);

                polarImage.setPixel(x, y, _image.pixel(xi, yi));

        }
    }
    _image = polarImage;
}

QImage RRLIImageHandler::makeRLI() {
    rgbToGrayScale();
    resize();
    QFile file(_imageParams->savePathForDatFile);
    file.open(QIODevice::WriteOnly);

    for(int y = 0; y < _image.height(); y++) {
        for(int x = 0; x < _image.width(); x++) {
            QColor clrCurrent(_image.pixel(x, y));
            if(_imageParams->pixelType == USHORT) {
                unsigned short value = (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3;
                value = setUshortPixelFormat(value);
                file.write((const char*) &value, sizeof(value));
            }
            else if(_imageParams->pixelType == UINT) {
                unsigned int value = (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3;
                value = setUintPixelFormat(value);
                file.write((const char*) &value, sizeof(value));
            }
            else if(_imageParams->pixelType == FLOAT) {
                float value = (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3;
                value = setFloatPixelFormat(value);
                file.write((const char*) &value, sizeof(value));
            }
        }
    }

    file.close();
    return _image;
}
