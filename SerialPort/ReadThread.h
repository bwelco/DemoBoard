#ifndef READTHREAD_H
#define READTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "qextserialport.h"
#include <QString>
#include <QTimer>
#include <QMutex>
#include <Queue/MyQueue.h>
#include "MainApplicationUI.h"

class MainApplicationUI;

class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(QextSerialPort * port);
    QextSerialPort * port;
    void run();
    void handle_message();
    void MyReadLine(int* readcount, char *readbuff_ret);
    char readbuf[100];
    char RecvBuff[1000];
    QTimer *CleanTimer;
    void GetMessageFromBuf(int *count, char *mess);
    bool isUseful(char* str);    
    MyQueue *que;

    QString arry;
    bool firstflag;
    bool endflag;
    int tempflag;

signals:
    void SendInfoToUI(QString mess);
private slots:
    void ReadMessage_V2();
};

#endif // READTHREAD_H
