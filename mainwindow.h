#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>

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

    unsigned getWidth(const QString &filepath);
    unsigned getHeight(const QString &filepath);

    std::vector<unsigned char> decodeImage(const QString &filepath);
    void encodeImage(const QString &filepath, std::vector<unsigned char>& image, unsigned width, unsigned height);
    void chb(std::vector<unsigned char> &image);

    void setImage(const QString &path);

    void doThisShit(const QString &filepath, const QString &savepath, unsigned h, unsigned w);

signals:
    void signalFromPathSlot(const QString &filepath, const QString &savepath);
    void signalPathDirSelect(const QString &filepath);


private slots:
    void slotPath();
    void slotInitDoThisShit(const QString &filepath, const QString &savepath);
    void slotGetPathWithDirSelect();
    void slotSetNameToPathLine(const QString &filepath);

};

#endif // MAINWINDOW_H
