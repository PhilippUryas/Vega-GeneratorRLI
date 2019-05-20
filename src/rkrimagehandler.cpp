 #include "rkrimagehandler.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

RKRImageHandler::RKRImageHandler(ImageParams& imageParams) :
                ImageHandler(imageParams) {}

RKRImageHandler::~RKRImageHandler() {}

void RKRImageHandler::rgbToGrayScale() {

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

QImage RKRImageHandler::makeRLI() {
    //thread->start();
    toPolar();
    rgbToGrayScale();
    qDebug() << "IMHERE";
    QFile file(_imageParams->savePathForDatFile);
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

    //thread->quit();

    return _image;
}
