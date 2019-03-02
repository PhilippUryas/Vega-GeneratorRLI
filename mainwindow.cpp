#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lodepng.h"
#include "imagelabel.h"
#include <QDebug>
#include <QFileDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::released, this, &MainWindow::slotPath);
    connect(this, &MainWindow::signalFromPathSlot, this, &MainWindow::slotInitDoThisShit);

    connect(ui->getPathToPathLineEdit, &QPushButton::released, this, &MainWindow::slotGetPathWithDirSelect);
    connect(this, &MainWindow::signalPathDirSelect, this, &MainWindow::slotSetNameToPathLine);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotGetPathWithDirSelect() {
    emit signalPathDirSelect(QFileDialog::getOpenFileName(this,
                            tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)")));
}

void MainWindow::slotPath() {
    qDebug() << "pathSlot";
    emit signalFromPathSlot(ui->pathLineEdit->text(), ui->saveLineEdit->text());
}

void MainWindow::slotInitDoThisShit(const QString &filepath, const QString &savepath) {
    qDebug() << filepath;
    qDebug() << savepath;
    MainWindow::doThisShit(filepath, savepath,
                           getWidth(filepath),
                           getHeight(filepath));
    ImageLabel il(filepath);
    il.setImage();
    //il.setImage(filepath);
    //Form::setImage(filepath);
}

void MainWindow::slotSetNameToPathLine(const QString &path) {
    ui->pathLineEdit->setText(path);
}

/* ДАЛЬШЕ КОСТЫЛИ
   ЛУЧШЕ ЭТОГО НЕ ВИДЕТЬ
   <==================8 */

void MainWindow::doThisShit(const QString &filepath, const QString &savepath, unsigned h, unsigned w) {

    std::string str = savepath.toStdString();
    const char* p = str.c_str();
    qDebug() << "Flag0";
    std::vector<unsigned char>  image = decodeImage(filepath);

    qDebug() << "Flag1";

    //unsigned error;

   // lodepng::State state;
    //error = lodepng_inspect(&w, &h, &state, &image[0], image.size());


    chb(image);
    qDebug() << "Flag";
    encodeImage(p, image, h, w);
}

unsigned MainWindow::getWidth(const QString &filepath) {
    unsigned width, height;
    std::string str = filepath.toStdString();
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, str);

    if(error) {
        qDebug() << error;
    }



    return width;
}

unsigned MainWindow::getHeight(const QString &filepath) {
    unsigned height, width;
     std::string str = filepath.toStdString();
     std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, str);

    if(error) {
        qDebug() << error;
    }

    return height;
}

std::vector<unsigned char> MainWindow::decodeImage(const QString &filepath) {

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    std::string str = filepath.toStdString();
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

void MainWindow::encodeImage(const QString &filepath, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
   std::string str = filepath.toStdString();
   const char* p = str.c_str();

  unsigned error = lodepng::encode(str, image, width, height);

  //if there's an error, display it
 // if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}



void MainWindow::chb(std::vector<unsigned char> &image) {
    unsigned int middle = 0;
    for(size_t i = 0; i < image.size()-4;i+=4) {
        middle = (image[i] + image[i+1] + image[i+2])/3;

        image[i]    = middle;
        image[i+1]  = middle;
        image[i+2]  = middle;

    }
}
