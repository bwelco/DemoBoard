#include "MyQueue.h"

MyQueue::MyQueue()
{
    this->head = new QueueNode();
    this->head->next = NULL;
}

void MyQueue::push(QString mess)
{
    QueueNode* p = this->head;
    while(NULL != p->next)
    {
        p = p->next;
    }
    QueueNode* newnode = new QueueNode(mess, NULL);
    p->next = newnode;
}

QString MyQueue::pop()
{
    QString temp;
    if(NULL == this->head->next)
        return NULL;
    temp = this->head->next->data;

    QueueNode* toDeleteNode = this->head->next;
    this->head->next = toDeleteNode->next;
    delete(toDeleteNode);
    return temp;
}

bool MyQueue::isEmpty()
{
    if(NULL == this->head->next)
        return true;
    else
        return false;
}

void MyQueue::PushFromFirst(QString message)
{
    QueueNode* newnode = new QueueNode(message, NULL);
    QueueNode* temp = this->head->next;
    this->head->next = newnode;
    newnode->next = temp;
}
