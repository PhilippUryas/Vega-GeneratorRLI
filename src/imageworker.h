#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include "imagelabel.h"

class ImageWorker
{
public:
    ImageWorker(const QString &path, const QString &savepath);
    void toChb();
    void toPolar(int targetH);

private:
    QString _filepath;
    QString _savepath;
    QImage _image;

};

#endif
