#include "mainwindow.h"
#include "rkrimagehandler.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>

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
    connect(ui->selectSourcePathPushButton, &QPushButton::released, this, &MainWindow::setSourcePathSlot);
    connect(ui->selectSavePathPushButton, &QPushButton::released, this, &MainWindow::setSavePathSlot);

    connect(ui->toPolarPushButton, &QPushButton::released, this, &MainWindow::initToPolarSlot);
}

void MainWindow::setSourcePathSlot() {
    ui->sourcePathLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Select image"),
                                                                 "/", tr("*png *jpg *bmp")));
}

void MainWindow::setSavePathSlot() {
    ui->savePathLineEdit->setText(QFileDialog::getSaveFileName(this, tr("Save image"),
                                                               "/", tr("*png *jpg *bmp")));
}

void MainWindow::initToPolarSlot() {

    bool okH = false;
    bool okW = false;
    int targetH = QInputDialog::getInt(this, tr("Target Heigth"),
                                    tr("Target Heigth: "), 0, 0, 1000000, 1, &okH);
    int targetW = QInputDialog::getInt(this, tr("Target width"),
                                    tr("Target width: "), 0, 0, 1000000, 1, &okW);
    if(okH && okW) {

        ImageParams ip;
        ip.path = ui->sourcePathLineEdit->text();
        ip.imageType = RKR;
        ip.pixelType = USHORT;
        ip.targetWidth = targetW;
        ip.targetHeight = targetH;

        RKRImageHandler rkrImage(ip);
        rkrImage.makeRKR();
        rkrImage.saveImage(ui->savePathLineEdit->text());
        rkrImage.saveToRLI("E:/1200x2500RKR_Vorkuta.dat");     //!!!
    }

}
