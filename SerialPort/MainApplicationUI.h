#ifndef MAINAPPLICATIONUI_H
#define MAINAPPLICATIONUI_H

#include <QWidget>
#include "ReadThread.h"
#include "WriteThread.h"
#include <QDebug>
#include "qextserialport.h"
#include <QString>
#include <queue>
#include <iostream>
#include <QEvent>
#include <QObject>
#include <Qmutex>
#include <QMouseEvent>
#include <QSlider>
#include <QLineEdit>
#include "Queue/MyQueue.h"
#include "SearchForSerialPort.h"
#include "ReadThread.h"
#include "WriteThread.h"
#include "LedChoose.h"

using namespace std;
class LedChoose;
class WriteThread;
class ReadThread;
namespace Ui {
class MainApplicationUI;
}

class MainApplicationUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainApplicationUI(QString comm, QWidget *parent = 0);
    ~MainApplicationUI();
    QString comm;
    ReadThread* read_thread;
    WriteThread* write_thread;
    QextSerialPort * port;
    MyQueue* que;    //发送队列(线程定时发 && ui操作发)
    QMutex* mutex;

    void SendMessageToQueue(QString message);
    bool eventFilter(QObject *o, QEvent *e);
    QSlider *slider;
    QLineEdit* steer;
    bool mousepreeslock = false;
    bool presslock = false;
    LedChoose *ledchoose;
    bool BmpOnOffFlag = false;
    bool RedLightFlag = false;
    bool SoundFlag = false;
    bool out1flag = false;
    bool out2flag = false;
    bool out3flag = false;
    bool CanChange = true;
    QTimer* ForbidChangeTimer;

   // void mousePressEvent(QMouseEvent *ev);
   // void mouseMoveEvent(QMouseEvent *ev);

private:
    Ui::MainApplicationUI *ui;
    void closeEvent(QCloseEvent *event);
signals:
    void SearchClose();
private slots:
    void RecvMessageTOUpdateUI(QString mess);
    void set_steer_cout(int pos);
    void ChangeButtonColor();
    void ChangeButtonColorBack();
    void ButtonClicked();
    void LedChooseResult(int index);
    void ForbidFlagSetFalse();
};

#endif // MAINAPPLICATIONUI_H
