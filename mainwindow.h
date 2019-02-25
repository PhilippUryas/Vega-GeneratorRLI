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
    std::vector<unsigned char> decodeImage(const QString &filepath);
    void encodeImage(const QString &filepath, std::vector<unsigned char>& image, unsigned width, unsigned height);
    void chb(std::vector<unsigned char> &image);

    void doThisShit(const QString &filepath, const QString &savepath, unsigned h, unsigned w);

signals:
    void signalFromPathSlot(const QString &filepath, const QString &savepath);

public slots:
    void slotPath();
    void initDoThisShit(const QString &filepath, const QString &savepath);

};

#endif // MAINWINDOW_H
