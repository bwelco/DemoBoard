#include "SerialThread.h"

SerialThread::SerialThread(QStringList comlist)
{
   this->comlist = comlist;
}

SerialThread::~SerialThread()
{
    delete(port);
    qDebug() << "Connect Serial Thread Exit.";
}

bool StartsWith(char *test, char *dst)
{
    char *p = test;
    char *q = dst;

    while( *q != '\0' )
    {
        if(*q != *p)
            return false;
        p++;
        q++;
    }
    return true;
}

void SerialThread::run()
{
    int count  = comlist.size();
    int ErrorCount = 0;
    QString temp;
    for(int i = 0; i < count; i++)
    {
        int AskTime = 0;
        char AskInfo[20] = "test*";
        char RetInfo[50];

        qDebug() << "Start Connecting:" << comlist.at(i);

        port = new QextSerialPort();
        port->setPortName(comlist.at(i));  //#define DEFAULT_PORT    "/dev/ttySAC2"  设置端口名
        port->setBaudRate(BAUD9600);  //#define DEFAULT_BAUD    BAUD38400     设置波特率
        port->setDataBits(DATA_8);
        port->setParity(PAR_NONE);
        port->setStopBits(STOP_1);
        port->setFlowControl(FLOW_OFF);
        port->setTimeout(10);
        if(false == port->open(QIODevice::ReadWrite))
        {
            qDebug() << "Open fail";
        }

        while(true)
        {
            emit this->SendInfo(comlist.at(i)+"连接中...");
            memset(RetInfo, 0, 50);
            port->write(AskInfo);
            port->readLine(RetInfo, 100);
            QThread::usleep(10000);
          //  qDebug() << "ret:" << RetInfo;
            if( StartsWith(RetInfo, "*return") )
            {
                /*连接成功*/
                port->close();  //关闭串口,到MainApplicationUI中再次打开
                qDebug() << comlist.at(i) << "Successfully Connect.";
                emit this->SendInfo("Success: 连接成功");
                emit this->SendInfo("COMINFO:" + comlist.at(i));                
                //delete(this);
                delete(port);
                this->exit();
                return;
            }
            QThread::sleep(1);
            AskTime++;

            if(AskTime == 5)     //查询失败次数
            {
                if(ErrorCount != 0)
                    temp+='\n';
                temp += "Fail: ";
                temp += comlist.at(i);
                temp += "连接超时";
                emit this->SendInfo(temp);
                ErrorCount++;
                break;
            }
        }
        port->close();
    }
}

