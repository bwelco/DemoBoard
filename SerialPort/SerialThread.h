#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QStringList>
#include "qextserialport.h"
#include "MainApplicationUI.h"
#include "ReadThread.h"
#include "WriteThread.h"

class SerialThread : public QThread
{
        Q_OBJECT
public:
    explicit SerialThread(QStringList comlist);
    QextSerialPort * port = new QextSerialPort();
    void run();
    QStringList comlist;    
    ~SerialThread();
signals:
    void SendInfo(QString mess);
private slots:
};

#endif // SERIALTHREAD_H
