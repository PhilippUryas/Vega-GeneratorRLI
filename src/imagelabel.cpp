#include "imagelabel.h"

void ImageLabel::setImage(const QImage &image) {

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}
