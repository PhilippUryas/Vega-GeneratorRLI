#include "imagelabel.h"
#include "mainwindow.h"
#include "rkrimagehandler.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setupButtons();
}

MainWindow::~MainWindow() {
    delete ui;   
}

void MainWindow::setupButtons() {
    connect(ui->selectSourcePathButton, &QPushButton::released, this, &MainWindow::setSourcePathSlot);
    connect(ui->selectSaveImagePathButton, &QPushButton::released, this, &MainWindow::setSaveImagePathSlot);
    connect(ui->selectDatSavePathLineEdit, &QPushButton::released, this, &MainWindow::setDatSavePathSlot);

    connect(ui->makeRLIButton, &QPushButton::released, this, &MainWindow::initToPolarSlot);
}

void MainWindow::setSourcePathSlot() {
    ui->sourcePathLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Select image"),
                                                                 "/", tr("*.png *.jpg *.bmp")));
}

void MainWindow::setSaveImagePathSlot() {
    ui->saveImageLineEdit->setText(QFileDialog::getSaveFileName(this, tr("Save image path"),
                                                                "/", tr("*.png *.jpg *.bmp")));
}

void MainWindow::setDatSavePathSlot() {
    ui->datFileSavePathLineEdit->setText(QFileDialog::getSaveFileName(this, tr("Save image"),
                                                               "/", tr("*.dat")));
}

void MainWindow::initToPolarSlot() {

   ImageParams ip;
   ip.sourceImagePath = ui->sourcePathLineEdit->text();
   ip.savePathForDatFile = ui->datFileSavePathLineEdit->text();
   ip.imageType = imageTypeParse();
   ip.pixelType = pixelTypeParse();
   ip.targetWidth = ui->targetWidthComboBox->value();
   ip.targetHeight = ui->targetHeigthComboBox->value();

   if(ip.imageType == SRLI) {

       ip.SRLIstart = QInputDialog::getInt(this, tr("Set start angle"),
                                            tr("Set start angle: "),0, 0, 360, 1);

       ip.SRLIend = QInputDialog::getInt(this, tr("Set start angle"),
                                            tr("Set start angle: "),ip.SRLIstart,
                                            ip.SRLIstart, 360, 1);

   }

   if(ip.sourceImagePath.isEmpty() || ip.savePathForDatFile.isEmpty()) {
       QMessageBox::critical(this, tr("Generator RLI"), tr("Введите путь к исходному файлу и путь для сохранения .dat файла."));
   } else {
       ImageHandler *rliImage = ImageHandler::create(ip);
       QImage image = rliImage->makeRLI();
       image.save(ui->saveImageLineEdit->text());

       ImageLabel::setImage(image);

   }



}

ImageType MainWindow::imageTypeParse() {
    if(ui->imageTypeComboBox->currentText() == "RKR") {
        return RKR;
    }
    else if(ui->imageTypeComboBox->currentText() == "SRLI") {
        return SRLI;
    }
    else if(ui->imageTypeComboBox->currentText() == "RRLI") {
        return RRLI;
    }
}

PixelType MainWindow::pixelTypeParse() {
    if(ui->pixelTypeComboBox->currentText() == "USHORT") {
        return USHORT;
    }
    else if(ui->pixelTypeComboBox->currentText() == "UINT") {
        return UINT;
    }
    else if(ui->pixelTypeComboBox->currentText() == "FLOAT") {
        return FLOAT;
    }
}
