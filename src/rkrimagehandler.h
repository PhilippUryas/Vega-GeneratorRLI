#ifndef RKRIMAGEHANDLER_H
#define RKRIMAGEHANDLER_H

#include "imagehandler.h"
#include <QImage>
#include <cmath>

class RKRImageHandler : public ImageHandler
{
public:
    RKRImageHandler(ImageParams& imageParams);
    ~RKRImageHandler() override;

    //void saveImage() override;
    QImage makeRLI() override;
private:
    void rgbToGrayScale();
    void toPolar();
};

#endif // RKRIMAGEHANDLER_H
