#include "ReadThread.h"
#include "MainApplicationUI.h"
ReadThread::ReadThread(QextSerialPort * port)
{
    this->port = port;
    this->que = new MyQueue();   //接收队列
    this->CleanTimer = new QTimer();

    firstflag = 0;
    tempflag = 0;
    endflag = 0;


    //memset(RecvBuff, 0, 1000);
    //strcpy(RecvBuff, "*start*\n");   //使得第一条消息正常，即第一条message为 start
    connect(port, SIGNAL(readyRead()), this, SLOT(ReadMessage_V2()));
   // connect(CleanTimer, SIGNAL(timeout()), this, SLOT(CleanBuff()));  //定期清空buff
   // CleanTimer->start(2000);  // 每2s清理一次buff，防止溢出
}


void ReadThread::run()
{
    //port->flush();    /*清空缓冲区*/

    while(true)
    {
       QThread::sleep(1);//
    }
}




void ReadThread::ReadMessage_V2()
{
    char ret;
    port->read(&ret, 1);  //每次只读一个字符
    static int i;

    if(ret == '*')     //找到头帧
    {
        tempflag = 1;
        return;
    }
    if( 1 == tempflag ) //找到头帧并初始化
    {
        i = 0;
        firstflag = 1;
        tempflag = 0;
        memset(readbuf,0,100);
    }
    if(ret == '#' && firstflag == 1)    //找到尾桢
    {
        //int count = i;
        readbuf[i] = '\0';
        qDebug() << "message:" << readbuf;

        emit this->SendInfoToUI(readbuf);
        firstflag = 0;
        i = 0;
    }
    if( firstflag == 1)
    {
        readbuf[i++] = ret;           // 中间部分复制
    }

}

