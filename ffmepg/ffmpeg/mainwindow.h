#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
extern "C"
{
#include "libavutil/log.h"
#include "libavcodec/avcodec.h"
   #include "libavformat/avformat.h"
   #include "libswscale/swscale.h"
   #include "libavdevice/avdevice.h"
   #include "libavutil/pixfmt.h"

}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
