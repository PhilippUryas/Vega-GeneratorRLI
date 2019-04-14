#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagelabel.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::released, this, &MainWindow::slotPath);
    connect(this, &MainWindow::signalFromPathSlot, this, &MainWindow::slotInitSetImage);

    connect(ui->getPathToPathLineEdit, &QPushButton::released, this, &MainWindow::slotGetPathWithDirSelect);
    connect(this, &MainWindow::signalPathDirSelect, this, &MainWindow::slotSetNameToPathLine);

    connect(ui->getPathToSaveLineEdit, &QPushButton::released, this, &MainWindow::slotGetSavePathWithDirSelect);
    connect(this, &MainWindow::signalSavePathDirSelect, this, &MainWindow::slotSetNameToSavePathLine);
}

MainWindow::~MainWindow() {

    delete ui;   
}

void MainWindow::slotGetSavePathWithDirSelect() {

    emit signalSavePathDirSelect(QFileDialog::getSaveFileName(this, tr("Save File"),
                                                              "/home/test.jpg",
                                                              tr("Images (*.png *.jpg *.bmp)")));
}

void MainWindow::slotGetPathWithDirSelect() {

    emit signalPathDirSelect(QFileDialog::getOpenFileName(this,
                            tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"))); /* *.jpg *.bmp z*/
}

void MainWindow::slotSetNameToSavePathLine(const QString &savepath) {

    ui->saveLineEdit->setText(savepath);
}

void MainWindow::slotSetNameToPathLine(const QString &path) {

    ui->pathLineEdit->setText(path);
}


void MainWindow::slotPath() {

    emit signalFromPathSlot(/*"/home/philipp/Документы/ава.jpg", "/home/philipp/Документы/ava.jpg"*/ui->pathLineEdit->text(), ui->saveLineEdit->text());
}

void MainWindow::slotInitSetImage(const QString &filepath, const QString &savepath) {

    ImageWorker png(filepath, savepath);
    //png.toPolar();
    png.toPolar(ui->spinBox->value());
    //png.sjatie(ui->spinBox->value());
    ImageLabel il(filepath);
   // il.makeImageBlack(savepath, il.getWidth(), il.getHeight());
    il.setImage(savepath);
}
