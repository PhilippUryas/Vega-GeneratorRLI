#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include "png.h"

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

signals:
    void signalFromPathSlot(const QString &filepath, const QString &savepath);

    void signalPathDirSelect(const QString &filepath);
    void signalSavePathDirSelect(const QString &savepath);


private slots:
    void slotPath();
    void slotInitSetImage(const QString &filepath, const QString &savepath);

    void slotGetPathWithDirSelect();
    void slotSetNameToPathLine(const QString &filepath);

    void slotGetSavePathWithDirSelect();
    void slotSetNameToSavePathLine(const QString &savepath);

};

#endif // MAINWINDOW_H
