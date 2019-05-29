#ifndef SRLIIMAGEHANDLER_H
#define SRLIIMAGEHANDLER_H

#include "imagehandler.h"

class SRLIImageHandler : public ImageHandler
{
public:
    SRLIImageHandler(ImageParams& imageParams);
    ~SRLIImageHandler() override;

    QImage makeRLI() override;


private:
    void toSector();

};

#endif // SRLIIMAGEHANDLER_H
