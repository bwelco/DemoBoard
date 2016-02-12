#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QObject>
#include <QThread>
#include "qextserialport.h"
#include "Queue/MyQueue.h"
#include <queue>
#include <iostream>
#include <QMutex>
#include <QTimer>
#include <QDebug>
#include "MainApplicationUI.h"

using namespace std;
class MainApplicationUI;

class WriteThread : public QThread
{
    Q_OBJECT
public:
    QextSerialPort* port;
    explicit WriteThread(QextSerialPort* port,
                         MyQueue* que, QMutex *mutex);
    void run();
    MyQueue* que;
    QMutex *mutex;
    bool QueueIsEmpty();
    QString GetQueueMessage();
    void SendMessageToQueue(QString message);
    QTimer* timer;
    QTimer* timer2;
    bool lockflag = true;

signals:

private slots:
    void SendAskInfoTimes();

};

#endif // WRITETHREAD_H
