#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QString>
#include <QImage>
#include <QThread>

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
    //Только для SRLI
    int SRLIstart;
    int SRLIend;
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

    ushort setUshortPixelFormat(ushort value);
    uint setUintPixelFormat(uint value);
    float setFloatPixelFormat(float value);

    void rgbToGrayScale();

    QImage _image;
    ImageParams* _imageParams;
};
#endif // IMAGEHANDLER_H
