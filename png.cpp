#include "png.h"

#include "QImage"
#include <iostream>
#include <cmath>
#include "math.h"
#include <utility>

PNG::PNG(const QString &filepath, const QString &savepath) {
    _filepath = filepath;
    _savepath = savepath;

    QImage image(filepath);
    _image = image;
}

void PNG::toChb() {

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

void PNG::toPolar() {
    int heightTransform = _image.height()*2+1;
    int widthTransform = _image.width();

    int centerX = _image.width()/2;
    int centerY = _image.height()/2;

    QImage polarImage(widthTransform, heightTransform,
                      QImage::Format_RGB32);

    for(int y = 0; y < _image.height(); y++) {
        for(int x = 0; x < _image.width(); x++) {

               double xx = x - centerX;
               double yy = y - centerY;

               double r = sqrt(xx*xx+yy*yy);
               double a = atan2(xx, yy) * 180.0 / M_PI;
               if (a < 0) {
                   a+=360;
               }

               xx = r;
               yy = centerY+a*(_image.height()/360.0);

               //QColor clrCurrent(_image.pixel(x, y));

               //qDebug() << r << " " << a;
               //qDebug() << xx << " " << yy;

               polarImage.setPixel(xx, yy, _image.pixel(x, y));
        }
    }

    polarImage.save(_savepath);
}

//void PNG::tocart() {}

// /home/philipp/workspace/c++/VegaProject/blackvkast.png
