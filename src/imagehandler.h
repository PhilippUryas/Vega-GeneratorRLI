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

    QString sourceImagePath;           //путь к исходному изображению
    QString savePathForDatFile;       //путь для сохранения .dat файла
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
    static ImageHandler* create(ImageParams& imageParams);

    virtual ~ImageHandler() = 0;
    virtual QImage makeRLI() = 0;

protected:
    ImageHandler(ImageParams& imageParams);

    ImageHandler* setPixelFormat();

    //Убрать \/
    //virtual void saveImage() = 0;

    ushort setUshortPixelFormat(ushort value);
    uint setUintPixelFormat(uint value);

    QImage _image;
    ImageParams* _imageParams;

private:

};
#endif // IMAGEHANDLER_H
