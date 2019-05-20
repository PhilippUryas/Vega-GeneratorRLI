#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <QThread>
#include "imagehandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setupButtons();

    ImageType imageTypeParse();
    PixelType pixelTypeParse();

private slots:
    void setSourcePathSlot();
    void setSaveImagePathSlot();
    void setDatSavePathSlot();

    void initToPolarSlot();

};

#endif // MAINWINDOW_H
