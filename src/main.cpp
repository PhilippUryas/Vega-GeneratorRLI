#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setFixedSize(335, 157);
    w.setWindowTitle("...");
    w.show();


    return a.exec();
}
