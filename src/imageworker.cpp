#include "imageworker.h"

#include "QImage"
#include <iostream>
#include <cmath>
#include "math.h"
#include <utility>

ImageWorker::ImageWorker(const QString &filepath, const QString &savepath) {
    _filepath = filepath;
    _savepath = savepath;

    QImage image(filepath);
    _image = image;
}

void ImageWorker::toChb() {

    for (int row = 0; row < _image.width(); row++) {
        for (int col = 0; col < _image.height(); col++)
        {
            QColor clrCurrent(_image.pixel( row, col ));

            QRgb chbColor;
            int middle = ((clrCurrent.red()+clrCurrent.green()+clrCurrent.blue())/3);
            chbColor = qRgb(middle, middle, middle);

            _image.setPixel(row, col, chbColor);
        }
    }

    _image.save(_savepath);

}

void ImageWorker::toPolar(int targetH) {
    int heightTransform = targetH;
    int widthTransform = _image.width()/2;

    int centerX = _image.width()/2;
    int centerY = _image.height()/2;

    QImage polarImage(widthTransform, heightTransform,
                      QImage::Format_RGB32);

    for(int f = 0; f < targetH; f++) {
        for(int r = 0; r < _image.width(); r++) {

                float fi = float(f)/targetH*2*M_PI;

                int x = centerX + r*cos(fi);
                int y = centerY - r*sin(fi);

                if(x <= _image.width() && y <= _image.height() && x >= 0 && y >= 0) {
                    polarImage.setPixel(r, f, _image.pixel(x, y));
                }

        }
    }

    polarImage = polarImage.scaled(_image.width(), _image.height(),
                     Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation);

    polarImage.save(_savepath);

}


