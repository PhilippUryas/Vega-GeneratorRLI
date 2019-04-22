#ifndef RKRIMAGEHANDLER_H
#define RKRIMAGEHANDLER_H

#include "imagehandler.h"
#include <QImage>
#include <cmath>

/* С кодом беда - будем править
 * */

class RKRImageHandler : public ImageHandler
{
public:
    RKRImageHandler(ImageParams& imageParams);
    ~RKRImageHandler() override;
    void makeRKR();

    void saveImage(const QString &savePath) override;
    void saveToRLI(const QString &savePath) override;
private:
    void rgbToGrayScale();
    void toPolar();
    void resizeByNearNeighboor();

};

#endif // RKRIMAGEHANDLER_H
