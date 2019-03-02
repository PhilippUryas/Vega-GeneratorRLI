#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QString>

class ImageLabel : public QLabel
{
private:
    QString m_path;


    unsigned getWidth(const QString &filepath);
    unsigned getHeight(const QString &filepath);
    std::vector<unsigned char> decodeImage(const QString &filepath);
    void encodeImage(const QString &filepath, std::vector<unsigned char>& image,
                     unsigned width, unsigned height);
    void chb(std::vector<unsigned char> &image);


public:
    ImageLabel(const QString &path);
    ~ImageLabel();
    void setImage();


};

#endif // IMAGELABEL_H
