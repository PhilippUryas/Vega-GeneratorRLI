#ifndef PNG_H
#define PNG_H

#include "imagelabel.h"

class PNG
{
public:
    PNG(const QString &path, const QString &savepath);
    void toChb();
    void toPolar();
private:
    QString _filepath;
    QString _savepath;
    QImage _image;

     struct PNGheader {
         unsigned sygnature[8];
         /* IHDR */
         unsigned width[4];
         unsigned heigth[4];
         unsigned bitDepth;
         unsigned colorType;
         unsigned sjatie;
         unsigned filtration;
         unsigned interlance;

      };
};

#endif // PNG_H
