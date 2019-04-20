#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QString>
#include <QImage>

enum ImageType {
    RKR = 0,
    SRLI,
    RRLI,
};

enum PixelType {
    USHORT = 0,
    UINT,
    FLOAT,

};

struct ImageParams {
    QString path;			//путь до входного изображения
    ImageType imageType;	//тип развертки
    PixelType pixelType;	//тип отсчета
    unsigned targetWidth;	//количество дальностных отсчетов итогового изображения
    unsigned targetHeight;	//количество азимутальных строк итогового изображения

};

/* потом уточним */
//struct RKRImageParams : public ImageParams{};		//параметры для ркр
//struct SRLIImageParams : public ImageParams;	//для секторов
//struct RRLIImageParams : public ImageParams;	//для прямоугольной

class ImageHandler {
public:
    ImageHandler(ImageParams& imageParams);
    virtual ~ImageHandler() = 0;

    virtual void saveImage(const QString &savePath) = 0;
    virtual void saveToRLI(const QString &savePath) = 0;
protected:
    ushort setUshortPixelFormat(QRgb value);

    QImage _image;
    ImageParams* _imageParams;

private:


};
#endif // IMAGEHANDLER_H
