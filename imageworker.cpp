#include "png.h"

#include "QImage"
#include <iostream>
#include <cmath>
#include "math.h"
#include <utility>

//Сжатие

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

void PNG::toPolar(int targetH, int targetW) {
    int heightTransform = targetH;
    int widthTransform = _image.width()/2;

    int centerX = _image.width()/2;
    int centerY = _image.height()/2;

    int transformCenterX = widthTransform/2;
    int transformCenterY = heightTransform/2;

    QImage polarImage(widthTransform, heightTransform,
                      QImage::Format_RGB32);

    for(int f = 0; f < targetH; f++) /*for(int y = 0; y < heightTransform; y++)*/ {
        for(int r = 0; r < _image.width(); r++) /*for(int x = 0; x < widthTransform; x++)*/ {
               //double xx = x - centerX;
               //double yy = centerY - y;

               //double r = sqrt(xx*xx+yy*yy);
               //double a = atan2(yy, xx) * 180.0 / M_PI ;

                float fi = float(f)/targetH*2*M_PI;

                int x = centerX + r*cos(fi);
                int y = centerY - r*sin(fi);

               //xx = r;
               //yy = a*(_image.height()/360.0);

               //QColor clrCurrent(_image.pixel(x, y));

               //qDebug() << r << " " << a;
               //qDebug() << xx << " " << yy;

                if(x <= _image.width() && y <= _image.height() && x >= 0 && y >= 0) {
                    polarImage.setPixel(r, f, _image.pixel(x, y));
                }

        }
    }

    polarImage = polarImage.scaled(_image.width(), _image.height(),
                     Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation);

    polarImage.save(_savepath);

}

void PNG::sjatie(int sj) {
    int heightTransform = _image.height();
    int widthTransform = _image.width();

    QImage sjImage(widthTransform*2, heightTransform, QImage::Format_RGB32)/*widthTransform, heightTransform,
                   QImage::Format_RGB32*/;

    //sjImage = _image.scaled(_image.width(), _image.height(), Qt::KeepAspectRatioByExpanding, Qt::TransformationMode::FastTransformation);


    for(int y = 0; y < heightTransform; y++) {
        int z = 0;
        for(int x = 0; x < widthTransform; x++, z+=3) {
            //uint Buffer = 0;
             sjImage.setPixel(z, y, _image.pixel(x, y));

             sjImage.setPixel(x+1, y, sjImage.pixel(x, y));

            //qDebug() << _image.pixelColor(x, y)

            //qDebug() << newColor << " " << redBuffer << " " << blueBuffer << " " << greenBuffer;
            //qDebug() << buffer;
            //sjImage.setPixel(x, y);

        }

    }
    sjImage.save(_savepath);

}

void PNG::billinearInterpolation() {
    double h_rate = 2.0;
    double w_rate = 2.0;
    QImage resultImg(_image.width(), _image.height(), QImage::Format_RGB32);
    for (int y = 0; y < resultImg.width() - 1; y++) {
            for (int x = 0; x < resultImg.height() - 1; x++) {
                int px = (int)(x / w_rate);
                int py = (int)(y / h_rate);

                if (px >= _image.width() - 1 || py >= _image.height() - 1) break;

                double fx1 = (double)x / (double)w_rate - (double)px;
                double fx2 = 1 - fx1;
                double fy1 = (double)y / (double)h_rate - (double)py;
                double fy2 = 1 - fy1;

                double w1 = fx2*fy2;
                double w2 = fx1*fy2;
                double w3 = fx2*fy1;
                double w4 = fx1*fy1;
                /*
                Vec3b p1 = image.at<Vec3b>(py, px);
                Vec3b p2 = image.at<Vec3b>(py, px + 1);
                Vec3b p3 = image.at<Vec3b>(py + 1, px);
                Vec3b p4 = image.at<Vec3b>(py + 1, px + 1);
                result_img.at<Vec3b>(y, x) = w1*p1 + w2*p2 + w3*p3 + w4*p4;
                */
            }
        }
}

