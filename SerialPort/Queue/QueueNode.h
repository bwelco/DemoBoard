#ifndef QUEUENODE_H
#define QUEUENODE_H

#include <iostream>
#include <QString>
#include "MyQueue.h"
using namespace std;

class QueueNode
{
public:
    QString data;
    QueueNode* next;
    QueueNode()
    {
        this->next = NULL;
    }
    QueueNode(QString data, QueueNode *next = NULL)
    {
        this->data = data;
        this->next = next;
    }
};

#endif // QUEUENODE_H
