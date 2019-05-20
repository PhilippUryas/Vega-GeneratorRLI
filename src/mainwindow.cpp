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
    connect(ui->selectDatSavePathLineEdit, &QPushButton::released, this, &MainWindow::setSavePathSlot);

    connect(ui->makeRLIButton, &QPushButton::released, this, &MainWindow::initToPolarSlot);
}

void MainWindow::setSourcePathSlot() {
    ui->sourcePathLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Select image"),
                                                                 "/", tr("*.png *.jpg *.bmp")));
}

void MainWindow::setSavePathSlot() {
    ui->datFileSavePathLineEdit->setText(QFileDialog::getSaveFileName(this, tr("Save image"),
                                                               "/", tr("*.png *.jpg *.bmp")));
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

}



ImageType MainWindow::imageTypeParse() {
    if(ui->imageTypeComboBox->count() == 0) {
        return RKR;
    }
    else if(ui->imageTypeComboBox->count() == 1) {
        return SRLI;
    }
    else if(ui->imageTypeComboBox->count() == 2) {
        return RRLI;
    }
}

PixelType MainWindow::pixelTypeParse() {
    if(ui->pixelTypeComboBox->count() == 0) {
        return USHORT;
    }
    else if(ui->pixelTypeComboBox->count() == 1) {
        return UINT;
    }
    else if(ui->pixelTypeComboBox->count() == 2) {
        return FLOAT;
    }
}
