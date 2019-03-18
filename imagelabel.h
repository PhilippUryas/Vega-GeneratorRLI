#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <string>
#include <vector>

class ImageLabel : public QLabel
{
private:
    QString m_path;

public:

    ImageLabel(const QString &savepath);

    ~ImageLabel();

    void setImage();
    void setImage(const QString &savepath);
};

#endif // IMAGELABEL_H
