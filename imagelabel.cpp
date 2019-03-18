#include "imagelabel.h"

//ImageLabel::ImageLabel() { }

ImageLabel::ImageLabel(const QString &savepath) {

    m_path = savepath;
}

ImageLabel::~ImageLabel() {

}

void ImageLabel::setImage() {
    QPixmap pixmap(m_path);
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    //label.setMask(pixmap.mask());
    label->show();
}

void ImageLabel::setImage(const QString &savepath) {
    QPixmap pixmap(savepath);
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    //label.setMask(pixmap.mask());
    label->show();
}

