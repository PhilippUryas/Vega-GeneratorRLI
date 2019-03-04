#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <string>
#include <vector>
#include <lodepng.h>

class ImageLabel : public QLabel
{
private:
    QString m_path;

    std::vector<unsigned char> decodeImage();
    void encodeImage(const QString &savepath,
                     std::vector<unsigned char>& image,
                     unsigned width, unsigned height);

    void chb(std::vector<unsigned char> &image);

public:
    //ImageLabel();
    ImageLabel(const QString &path);
    //ImageLabel(const QString &path, const QString &savepath);

    ~ImageLabel();

    void makeImageBlack(const QString &savepath,
                        unsigned h, unsigned w);

    unsigned getWidth();
    unsigned getHeight();

    void setImage();
    void setImage(const QString &savepath);


};

#endif // IMAGELABEL_H
