#include "mainwindow.h"
#include "rkrimagehandler.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>

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

   ImageHandler *rliImage = ImageHandler::create(ip);
   QImage image = rliImage->makeRLI();
   image.save(ui->saveImageLineEdit->text());

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
