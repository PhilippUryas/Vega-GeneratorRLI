#include "rkrimagehandler.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

RKRImageHandler::RKRImageHandler(ImageParams& imageParams) :
                ImageHandler(imageParams) {
}

RKRImageHandler::~RKRImageHandler() {

}

void RKRImageHandler::makeRKR() {

    toPolar();

    /* НЕ нужен */
    //resizeByNearNeighboor();

    rgbToGrayScale();
}

void RKRImageHandler::rgbToGrayScale() {

    for (int row = 0; row < _image.width(); row++) {
        for (int col = 0; col < _image.height(); col++)
        {
            QColor clrCurrent(_image.pixel( row, col ));

            QRgb chbColor;
            int grayScale = 0.299*clrCurrent.red() + 0.587*clrCurrent.green() + 0.114*clrCurrent.blue();
            chbColor = qRgb(grayScale, grayScale, grayScale);

            _image.setPixel(row, col, chbColor);
        }
    }
}

void RKRImageHandler::toPolar() {

    unsigned heightTransform = _imageParams->targetHeight;
    unsigned widthTransform = _imageParams->targetWidth;

    int centerX = _image.width()/2;
    int centerY = _image.height()/2;

    QImage polarImage(widthTransform, heightTransform,
                      QImage::Format_RGB32);

    for(int f = 0; f < heightTransform; f++) {
        for(int r = 0; r < widthTransform; r++) {

                float fi = float(f)/(heightTransform - 1) * 2*M_PI;

                int x = centerX + r*cos(fi);
                int y = centerY - r*sin(fi);

                if(x < _image.width() && y < _image.height() && x >= 0 && y >= 0) {
                    polarImage.setPixel(r, f, _image.pixel(x, y));
                }

        }
    }
    //polarImage.save("E:/ress.bmp");
    _image = polarImage;
}

void RKRImageHandler::resizeByNearNeighboor() {

    QImage newCartImage(_imageParams->targetWidth, _image.height(), QImage::Format_RGB32);
    for(int y = 0; y < _image.height(); y++) {
        for(int x = 0; x < _imageParams->targetHeight; x++) {
            unsigned newX = float(x)/_imageParams->targetWidth*(_image.width()-1);
            newCartImage.setPixel(x, y, _image.pixel(newX, y));
        }
    }

    _image = newCartImage;
}


void RKRImageHandler::saveImage(const QString &savePath) {
    _image.save(savePath);
}

void RKRImageHandler::saveToRLI(const QString &savePath) {
    QFile file(savePath);
    file.open(QIODevice::WriteOnly);
    //QTextStream fileStream(&file);

    /* "Строка" файла - один азимут
     * (последовательно пишем азимуты, а не дальности)
     * */
    for(int y = 0; y < _image.height(); y++) {
        for(int x = 0; x < _image.width(); x++) {
            QColor clrCurrent(_image.pixel(x, y));
            unsigned short value = (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3;
            value = setUshortPixelFormat(value);
            file.write((const char*) &value, sizeof(value));
        }
    }

    file.close();
}

