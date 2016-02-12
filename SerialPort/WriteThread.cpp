#include "WriteThread.h"
#include "MainApplicationUI.h"
WriteThread::WriteThread(QextSerialPort* port, MyQueue* que,
                         QMutex *mutex)
{
    this->port = port;


    this->que = que;
    this->mutex = mutex;

    SendMessageToQueue("GETALLFLAGINIT");
    this->timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(SendAskInfoTimes()));
    timer->start(1700);

}

bool WriteThread::QueueIsEmpty()
{
    mutex->lock();     //加锁

    bool is = 1;
    if(que->isEmpty())
        is = true;
    else
        is = false;

    mutex->unlock();  //解锁

    return is;
}

QString WriteThread::GetQueueMessage()
{
    mutex->lock();
    QString temp = que->pop();
    mutex->unlock();
    return temp;
}


void WriteThread::SendMessageToQueue(QString message)
{
    mutex->lock();
    que->push(message);
    mutex->unlock();
}

void WriteThread::SendAskInfoTimes()
{
    SendMessageToQueue("GETALLSTATE*");
}

void WriteThread::run()
{
    QString message;
    while(true)
    {
        while(true == this->QueueIsEmpty())
        {
            QThread::usleep(100000);    //每0.01s检查一次队列是否为空
        }
        /*不为空*/
        message = GetQueueMessage();


      //  qint64 count = port->write(message.toLatin1().data());
        port->write(message.toLatin1().data());


        if(message.startsWith("SETSTEER"))
        {
            QThread::usleep(1000000);
        }
        if(message.startsWith("SETRGB"))
        {
            QThread::usleep(1000000);
        }
        else
        {
            QThread::usleep(500000);
        }
    }
}
