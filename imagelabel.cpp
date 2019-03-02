#include "imagelabel.h"

ImageLabel::ImageLabel(const QString &path)
{
    m_path = path;
}

void ImageLabel::setImage() {
    QPixmap pixmap(m_path);
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    //label.setMask(pixmap.mask());
    label->show();
}
