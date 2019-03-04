#include "imagelabel.h"

//ImageLabel::ImageLabel() { }

ImageLabel::ImageLabel(const QString &path)
{
    m_path = path;
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

unsigned ImageLabel::getWidth() {
    unsigned width, height;
    std::string str = m_path.toStdString();
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, str);

    if(error) {
        qDebug() << error;
    }

    return width;
}

unsigned ImageLabel::getHeight() {
    unsigned height, width;
    std::string str = m_path.toStdString();
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, str);

    if(error) {
        qDebug() << error;
    }

    return height;
}

std::vector<unsigned char> ImageLabel::decodeImage() {

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    std::string str = m_path.toStdString();
    const char* p = str.c_str();

      //decode
    unsigned error = lodepng::decode(image, width, height, str);

    if(error) {
        qDebug() << error;
    }

    qDebug() << width;
    qDebug() << height;
      //if there's an error, display it
    //if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

      //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
    return image;
}

void ImageLabel::encodeImage(const QString &savepath, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
   std::string str = savepath.toStdString();
   const char* p = str.c_str();

  unsigned error = lodepng::encode(str, image, width, height);

  //if there's an error, display it
 // if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void ImageLabel::chb(std::vector<unsigned char> &image) {
    unsigned int middle = 0;
    for(size_t i = 0; i < image.size()-4;i+=4) {
        middle = (image[i] + image[i+1] + image[i+2])/3;

        image[i]    = middle;
        image[i+1]  = middle;
        image[i+2]  = middle;

    }
}

void ImageLabel::makeImageBlack(const QString &savepath, unsigned int h, unsigned int w) {

    std::string str = savepath.toStdString();
    const char* p = str.c_str();
    qDebug() << "Flag0";
    std::vector<unsigned char>  image = decodeImage();

    qDebug() << "Flag1";

    chb(image);
    qDebug() << "Flag";
    encodeImage(savepath, image, h, w);

}
