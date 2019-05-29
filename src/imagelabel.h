#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QString>

class ImageLabel : public QLabel
{
public:
    static void setImage(const QImage &image);

};

#endif // IMAGELABEL_H
