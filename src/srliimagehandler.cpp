#include "srliimagehandler.h"
#include <math.h>
#include <QDebug>
#include <QFile>

SRLIImageHandler::SRLIImageHandler(ImageParams &imageParams)
    : ImageHandler (imageParams){}

SRLIImageHandler::~SRLIImageHandler(){}

void SRLIImageHandler::toSector() {

    int centerX = _image.width()/2;
    int centerY = _image.height()/2;

    QImage polarImage(_imageParams->targetWidth, _imageParams->targetHeight,
                      QImage::Format_RGB32);

    for(int f = 0; f < _imageParams->targetHeight; f++) {
        for(int r = 0; r < _imageParams->targetWidth; r++) {    

            //перевод полярного изображения в полярное
            float fi = float(f)/_imageParams->targetHeight * 2*M_PI;

            int x = centerX + r*cos(fi);
            int y = centerY - r*sin(fi);

            //float sectorMin = (M_PI * (_imageParams->targetWidth/2) * (_imageParams->targetWidth/2)) * 30 / 360;
            if(x < _image.width() && y < _image.height() && x >= 0 && y >= 0 &&
                    fi > (_imageParams->SRLIstart * M_PI / 180)
                    && fi < (_imageParams->SRLIend * M_PI / 180)) {
                polarImage.setPixel(r, f, _image.pixel(x, y));
            }
        }
    }

    _image = polarImage;
}

QImage SRLIImageHandler::makeRLI(){
    toSector();
    rgbToGrayScale();

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
