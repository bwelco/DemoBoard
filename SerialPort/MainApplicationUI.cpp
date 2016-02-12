#include "MainApplicationUI.h"
#include "ui_mainapplicationui.h"


MainApplicationUI::MainApplicationUI(QString comm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainApplicationUI)
{
    ui->setupUi(this);
    this->comm = comm;
    this->que = new MyQueue();   //队列初始化
    this->mutex = new QMutex();         //队列锁初始化


    /* 重新启动串口，开始读写 */
    port = new QextSerialPort();
    port->setPortName(comm);  //#define DEFAULT_PORT    "/dev/ttySAC2"  设置端口名
    port->setBaudRate(BAUD9600);  //#define DEFAULT_BAUD    BAUD38400     设置波特率
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
    port->setTimeout(10);
    port->open(QIODevice::ReadWrite);


    qDebug() << "Starting Read and Write at "+comm ;

    /* 读线程启动 */
    this->read_thread = new ReadThread(port);
    this->read_thread->start();
    /* 写线程启动 */
    this->write_thread = new WriteThread(port, que, mutex);
    // port:端口 que:队列 mutex:队列锁
    this->write_thread->start();
    QThread::sleep(1);
    connect(this->read_thread,SIGNAL(SendInfoToUI(QString)), \
            this, SLOT(RecvMessageTOUpdateUI(QString)));
    connect(this->ui->ledbutton, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->ledbutton, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->bpmbutton, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->bpmbutton, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->redlightbutton, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->redlightbutton, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->soundbutton, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->soundbutton, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->setbutton1, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->setbutton1, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->setbutton2, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->setbutton2, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->out1button, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->out1button, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->out2button, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->out2button, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));
    connect(this->ui->out3button, SIGNAL(pressed()), this, SLOT(ChangeButtonColor()));
    connect(this->ui->out3button, SIGNAL(released()), this, SLOT(ChangeButtonColorBack()));

    connect(this->ui->ledbutton, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->bpmbutton, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->redlightbutton, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->soundbutton, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->setbutton1, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->setbutton2, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->out1button, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->out2button, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
    connect(this->ui->out3button, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));

    ForbidChangeTimer = new QTimer();
    connect(this->ForbidChangeTimer, SIGNAL(timeout()), this, SLOT(ForbidFlagSetFalse()));


  //  connect(this->ui->TempBackView, SIGNAL(clicked(bool))), this, SLOT(ButtonClicked());

   // connect(this->ui->steer_test, SIGNAL(valueChanged(int)), this, SLOT(set_steer_cout(int)));

  //  steer = this->ui->steer_count;
  //  this->ui->steer_count->installEventFilter(this);
    this->ui->steer_set->setPlaceholderText("请输入舵机值");
    this->ui->cardid_set->setPlaceholderText("请输入卡值");

    this->ui->temp_max->setPlaceholderText("温度上限");
    this->ui->temp_min->setPlaceholderText("温度下限");
    this->ui->humi_max->setPlaceholderText("湿度上限");
    this->ui->humi_min->setPlaceholderText("湿度下限");
    this->ui->light_max->setPlaceholderText("光照上限");
    this->ui->light_min->setPlaceholderText("光照下限");
    this->slider = this->ui->steer_test;
    this->slider->installEventFilter(this);
    this->slider->setMaximum(180);
    this->slider->setMinimum(0);
    emit this->SearchClose();

}

void MainApplicationUI::ForbidFlagSetFalse()
{
    this->CanChange = true;
    this->ForbidChangeTimer->stop();
}

void MainApplicationUI::SendMessageToQueue(QString message)
{
    mutex->lock();
    que->push(message);
    mutex->unlock();
}

bool MainApplicationUI::eventFilter(QObject *o, QEvent *e)
{

    if(o == (QObject*)slider && e->type() == QEvent::MouseMove)
    {
        mousepreeslock = true;
        return false;
    }
    if(o == (QObject*)slider && e->type() == QEvent::MouseButtonPress && !(
            e->type() == QEvent::MouseMove) && mousepreeslock == false)
    {
        presslock = true;

    }
    if(o == (QObject*)slider && e->type() == QEvent::MouseButtonRelease)
    {
        if(presslock == true && mousepreeslock == false)   //单击事件
        {
            int duration = slider->maximum() - slider->minimum();
            int pos = slider->minimum() + duration * ((double)((QMouseEvent*)e)->x() / slider->width());
            if(pos != slider->sliderPosition())
            {
                if(pos >= 180)
                    pos = 180;
                if(pos <= 0)
                    pos = 0;
               slider->setValue(pos);
               QString temp = QString::number(pos);
               this->ui->steer_count_label->setText(temp);
               QString temp2;
               temp2+="SETSTEER";
               temp2+=QString::number(pos);
               temp2+="*";
             //  qDebug() << temp2;
               SendMessageToQueue(temp2);
            }
            presslock = false;
        }
        else
        {
            int duration = slider->maximum() - slider->minimum();
            int pos = slider->minimum() + duration * ((double)((QMouseEvent*)e)->x() / slider->width());
            if(pos != slider->sliderPosition())
            {
                if(pos >= 180)
                    pos = 180;
                if(pos <= 0)
                    pos = 0;
               slider->setValue(pos);
               QString temp = QString::number(pos);
               this->ui->steer_count_label->setText(temp);
               QString temp2;
               temp2+="SETSTEER";
               temp2+=QString::number(pos);
               temp2+="*";
            //   qDebug() << temp2;
               SendMessageToQueue(temp2);
            }
            mousepreeslock = false;
        }
    }

}

void MainApplicationUI::ChangeButtonColor()
{
    QPushButton *button = (QPushButton*)sender();
    button->setStyleSheet(QLatin1String("border-style:outset;\n"
"color: rgb(255, 255, 255);\n"
"border-width:2;\n"
"border-color: rgb(255, 0, 0);"));

}

void MainApplicationUI::ChangeButtonColorBack()
{
    QPushButton *button = (QPushButton*)sender();

    button->setStyleSheet(QLatin1String("border-style:outset;\n"
    "color: rgb(255, 255, 255);\n"
    "border-width:1;\n"
    "border-color: rgb(255, 255, 255);"));

}

MainApplicationUI::~MainApplicationUI()
{
    delete ui;
}

void MainApplicationUI::set_steer_cout(int pos)
{
    QString temp = QString::number(pos);
    this->ui->steer_count_label->setText(temp);
}

void MainApplicationUI::ButtonClicked()
{
    QPushButton *button = (QPushButton*)sender();
    if(button == this->ui->ledbutton)
    {
        qDebug() << "ledbutton clicked";
        ledchoose = new LedChoose(this, NULL);
        ledchoose->setWindowTitle("请选择颜色");
        ledchoose->show();
    }

    if(button == ui->out1button)
    {
        if(out1flag == false)
        {
            this->ui->out1button->setText("\n\n\nON");
            out1flag = true;
            QString mes = "OUT1ON*";
            SendMessageToQueue(mes);
        }
        else if(out1flag == true)
        {
            this->ui->out1button->setText("\n\n\nOFF");
            out1flag = false;
            QString mes = "OUT1OFF*";
            SendMessageToQueue(mes);
        }

    }

    if(button == ui->out2button)
    {
        if(out2flag == false)
        {
            this->ui->out2button->setText("\n\n\nON");
            out2flag = true;
            QString mes = "OUT2ON*";
            SendMessageToQueue(mes);
        }
        else if(out2flag == true)
        {
            this->ui->out2button->setText("\n\n\nOFF");
            out2flag = false;
            QString mes = "OUT2OFF*";
            SendMessageToQueue(mes);
        }

    }

    if(button == ui->out3button)
    {
        if(out3flag == false)
        {
            this->ui->out3button->setText("\n\n\nON");
            out3flag = true;
            QString mes = "OUT3ON*";
            SendMessageToQueue(mes);
        }
        else if(out3flag == true)
        {
            this->ui->out3button->setText("\n\n\nOFF");
            out3flag = false;
            QString mes = "OUT3OFF*";
            SendMessageToQueue(mes);
        }


    }

    if(button == this->ui->bpmbutton)
    {
        if(BmpOnOffFlag == false)
        {
            this->ui->bpmbutton->setText("蜂鸣器:ON");
            BmpOnOffFlag = true;
            QString mes = "BPMON*";
            SendMessageToQueue(mes);
        }
        else if(BmpOnOffFlag == true)
        {
            this->ui->bpmbutton->setText("蜂鸣器:OFF");
            BmpOnOffFlag = false;
            QString mes = "BPMOFF*";
            SendMessageToQueue(mes);
        }
    }

    if(button == this->ui->redlightbutton)
    {
        if(RedLightFlag == false)
        {
            this->ui->redlightbutton->setText("红外联动:ON");
            RedLightFlag = true;
            QString mes = "LIGHTFLAG1*";
            SendMessageToQueue(mes);
        }
        else if(RedLightFlag == true)
        {
            this->ui->redlightbutton->setText("红外联动:OFF");
            RedLightFlag = false;
            QString mes = "LIGHTFLAG0*";
            SendMessageToQueue(mes);
        }
    }

    if(button == this->ui->soundbutton)
    {
        if(SoundFlag == false)
        {
            this->ui->soundbutton->setText("声音联动:ON");
            SoundFlag = true;
            QString mes = "SOUNDFLAG1*";
            SendMessageToQueue(mes);
        }
        else if(SoundFlag == true)
        {
            this->ui->soundbutton->setText("声音联动:OFF");
            SoundFlag = false;
            QString mes = "SOUNDFLAG0*";
            SendMessageToQueue(mes);
        }
    }
    if(button == this->ui->setbutton1)
    {
        if(this->ui->cardid_set->text() == "" && this->ui->steer_set->text() == "")
        {
            QMessageBox::information(NULL, "提示",
                                     "请输入卡号和舵机值！", QMessageBox::Yes |QMessageBox::No, QMessageBox::Yes);
        }
        else if(this->ui->cardid_set->text() == "")
        {
            QMessageBox::information(NULL, "提示",
                                     "请输入卡号！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        else if(this->ui->steer_set->text() == "")
        {
            QMessageBox::information(NULL, "提示",
                                     "请输入舵机值！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        else if(!(this->ui->cardid_set->text() == "" && this->ui->steer_set->text() == ""))
        {
            QString cardid;
            cardid += "CARDSET";
            cardid += this->ui->cardid_set->text();
            cardid += "*";
            SendMessageToQueue(cardid);

            QString steercount;
            steercount += "STEERSET";
            steercount += this->ui->steer_set->text();
            steercount += "*";
            SendMessageToQueue(steercount);
            QMessageBox::information(NULL, "提示",
                                     "设置成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    if(button == this->ui->setbutton2)
    {
       QString tempmaxc = this->ui->temp_max->text();
       QString tempminc = this->ui->temp_min->text();
       QString humimaxc = this->ui->humi_max->text();
       QString humiminc = this->ui->humi_min->text();
       QString lightmaxc = this->ui->light_max->text();
       QString lightminc = this->ui->light_min->text();

       QString tempmax = "SETMAXTEMP" + tempmaxc + "*";
       QString tempmin = "SETMINTEMP" + tempminc + "*";
       QString humimax = "SETMAXHUMI" + humimaxc + "*";
       QString humimin = "SETMINHUMI" + humiminc + "*";
       QString lightmax = "SETMAXLIGHT" + lightmaxc + "*";
       QString lightmin = "SETMINLIGHT" + lightminc + "*";

       QString all;
       if(tempmaxc == ""){
           tempmaxc = "未设置      ";
       }
       if(tempminc == ""){
           tempminc = "未设置      ";
       }
       if(humimaxc == ""){
           humimaxc = "未设置      ";
       }
       if(humiminc == ""){
           humiminc = "未设置      ";
       }
       if(lightmaxc == ""){
           lightmaxc = "未设置      ";
       }
       if(lightminc == ""){
           lightminc = "未设置      ";
       }

       all += ("   温度上限：" + tempmaxc + "      \n");
       all += ("   温度下限：" + tempminc + "      \n");
       all += ("   湿度上限：" + humimaxc + "      \n");
       all += ("   湿度下限：" + humiminc + "      \n");
       all += ("   光照上限：" + lightmaxc + "      \n");
       all += ("   光照下限：" + lightminc + "      \n");
       int ret = QMessageBox::information(NULL, "提示",
                                all, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
       if(ret == QMessageBox::Yes)
       {
           SendMessageToQueue(tempmax);
           SendMessageToQueue(tempmin);
           SendMessageToQueue(humimax);
           SendMessageToQueue(humimin);
           SendMessageToQueue(lightmax);
           SendMessageToQueue(lightmin);
       }
    }
    CanChange = false;
    this->ForbidChangeTimer->start(1200);
}

void MainApplicationUI::LedChooseResult(int index)
{
    QStringList strList;
    strList.append("无色(关闭)");
    strList.append("红色");
    strList.append("绿色");
    strList.append("蓝色");
    strList.append("青色");
    strList.append("黄色");
    strList.append("品红");
    strList.append("白色");
    qDebug() << strList.at(index);
    this->ui->ledbutton->setText("LED:"+strList.at(index));

    switch(index)
    {
            case 0:{
                QString temp2 = "SETRGB111*";
                SendMessageToQueue(temp2);
                break;
        }
            case 1:{
                QString temp = "SETRGB011*";
                SendMessageToQueue(temp);
                port->write(temp.toLatin1().data());
                QThread::usleep(1000000);
                QString temp2 = "SETMYLED011*";
                SendMessageToQueue(temp2);
                port->write(temp2.toLatin1().data());
                break;
        }
            case 2:{
                QString temp = "SETRGB101*";
                SendMessageToQueue(temp);

                QThread::usleep(1000000);
                QString temp2 = "SETMYLED101*";
                SendMessageToQueue(temp2);
                break;
        }
            case 3:{
                QString temp = "SETRGB110*";
                SendMessageToQueue(temp);
               QThread::usleep(1000000);
                QString temp2 = "SETMYLED110*";
                SendMessageToQueue(temp2);
                break;
        }
            case 4:{
                QString temp = "SETRGB100*";
                SendMessageToQueue(temp);
                QThread::usleep(1000000);
                QString temp2 = "SETMYLED100*";
                SendMessageToQueue(temp2);
                break;
        }
            case 5:{
                QString temp = "SETRGB001*";
                SendMessageToQueue(temp);
               QThread::usleep(1000000);
                QString temp2 = "SETMYLED001*";
                SendMessageToQueue(temp2);
                break;
        }
            case 6:{
                QString temp = "SETRGB010*";
                SendMessageToQueue(temp);
               QThread::usleep(1000000);
                QString temp2 = "SETMYLED010*";
                SendMessageToQueue(temp2);
                break;
        }
            case 7:{
                QString temp = "SETRGB000*";
                SendMessageToQueue(temp);
                QThread::usleep(1000000);
                QString temp2 = "SETMYLED000*";
                SendMessageToQueue(temp2);
                break;
        }
    }

}

void MainApplicationUI::RecvMessageTOUpdateUI(QString mess)
{
    if(CanChange == true)
    {
        if(mess.startsWith("T = "))
            this->ui->temp_count->setText(mess.mid(4));
        else if(mess.startsWith("R = "))
            this->ui->humi_count->setText(mess.mid(4));
        else if(mess.startsWith("light = "))
            this->ui->light_count->setText(mess.mid(8));
        else if(mess.startsWith("out1 = "))
        {
             if(mess.mid(7).startsWith("1"))
             {
                 this->ui->out1button->setText("\n\n\nOFF");
             }
             if(mess.mid(7).startsWith("0"))
             {
                 this->ui->out1button->setText("\n\n\nON");
             }
        }

        else if(mess.startsWith("out2 = "))
        {
             if(mess.mid(7).startsWith("1"))
             {
                 this->ui->out2button->setText("\n\n\nOFF");
             }
             if(mess.mid(7).startsWith("0"))
             {
                 this->ui->out2button->setText("\n\n\nON");
             }
        }

        else if(mess.startsWith("out3 = "))
        {
             if(mess.mid(7).startsWith("1"))
             {
                 this->ui->out3button->setText("\n\n\nOFF");
             }
             if(mess.mid(7).startsWith("0"))
             {
                 this->ui->out3button->setText("\n\n\nON");
             }
        }

        else if(mess.startsWith("card id = "))
        {
            this->ui->card_id->setText("卡号: "+mess.mid(10));
            this->ui->cardid_set->setText(mess.mid(10));
        }
        else if(mess.startsWith("sound = 1"))
        {
            this->ui->soundbutton->setText("声音联动:ON");
        }
        else if(mess.startsWith("sound = 0"))
        {
            this->ui->soundbutton->setText("声音联动:OFF");
        }
        else if(mess.startsWith("bpm = 0"))
        {
            this->ui->bpmbutton->setText("蜂鸣器:OFF");
        }
        else if(mess.startsWith("bpm = 1"))
        {
            this->ui->bpmbutton->setText("蜂鸣器:ON");
        }
        else if(mess.startsWith("redlight = 1"))
        {
            this->ui->redlightbutton->setText("红外联动:ON");
        }
        else if(mess.startsWith("redlight = 0"))
        {
            this->ui->redlightbutton->setText("红外联动:OFF");
        }
    }
}

void MainApplicationUI::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作

    port->close();
}

