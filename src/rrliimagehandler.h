#ifndef RRLIIMAGEHANDLER_H
#define RRLIIMAGEHANDLER_H

#include "imagehandler.h"

class RRLIImageHandler : public ImageHandler
{
public:
    RRLIImageHandler(ImageParams& imageParams);
    ~RRLIImageHandler() override;

    QImage makeRLI() override;
private:
    void resize();
};

#endif // RRLIIMAGEHANDLER_H
