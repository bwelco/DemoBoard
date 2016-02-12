#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <QDebug>
#include <Queue/QueueNode.h>
#include <iostream>
using namespace std;

class QueueNode;
class MyQueue
{
public:
    MyQueue();
    QueueNode* head;
    void push(QString mess);
    void PushFromFirst(QString message);
    QString pop();
    bool isEmpty();
};

#endif // MYQUEUE_H
