#include "SearchForSerialPort.h"

SearchForSerialPort::SearchForSerialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForSerialPort)
{
    ui->setupUi(this);
    timer = new QTimer();

    standardItemModel = new QStandardItemModel(this);

    strList = new QStringList();
    comlist = new QStringList();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
      //  qDebug() << "Name        : " << info.portName();
      //  qDebug() << "Description : " << info.description();
      //  qDebug() << "Manufacturer: " << info.manufacturer();

        QSerialPort serial;
        serial.setPort(info);

        QString* temp = new QString("接口:"+info.portName()+" 信息:"+info.description());
        strList->append(*temp);
        comlist->append(info.portName());

    }

    int nCount = strList->size();
    if(nCount == 0)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">\345\257\271\344\270\215\350\265\267\357\274\214\346\262\241\346\234\211\346\211\276\345\210\260\346\216\245\345\217\243</span></p></body></html>", 0));
    }
    else{

        for(int i = 0; i < nCount; i++)
        {
            QString string = static_cast<QString>(strList->at(i));
            QStandardItem *item = new QStandardItem(string);

            standardItemModel->appendRow(item);
        }

        itemClicked();
    }



}

void SearchForSerialPort::itemClicked()
{
    QString comm;
    comm = comlist->at(0);

    QString textview = comm;
    textview += "连接中";
    char *text = textview.toLatin1().data();

    ui->label_2->setText(QApplication::translate(text, 0));

   // connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    //timer->start(200);

    thread = new SerialThread(*comlist);
    thread->start();
    connect(thread, SIGNAL(SendInfo(QString)), this, SLOT(RecvUI(QString)));

}

SearchForSerialPort::~SearchForSerialPort()
{
    delete ui;
}

void SearchForSerialPort::printf(QString text)
{
    qDebug() << text;
}
void SearchForSerialPort::updateUI()
{
    TimberCount++;
    if(TimberCount % 5 == 1)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">接口连接中.</span></p></body></html>", 0));
    }

    if(TimberCount % 5 == 2)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">接口连接中..</span></p></body></html>", 0));
    }

    if(TimberCount % 5 == 3)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">接口连接中...</span></p></body></html>", 0));
    }

    if(TimberCount % 5 == 4)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">接口连接中....</span></p></body></html>", 0));
    }

    if(TimberCount % 5 == 0)
    {
        ui->label_2->setText(QApplication::translate("SearchForSerialPort", "<html><head/><body><p><span style=\" font-size:14pt;\">接口连接中.....</span></p></body></html>", 0));
    }

}

void SearchForSerialPort::RecvUI(QString message)
{
    QFont ft;
    ft.setPointSize(12);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    ui->label_2->setPalette(pe);

    ui->label_2->setFont(ft);
    ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    if(message.startsWith("Fail:"))
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);
        ui->label_2->setPalette(pe);
        ui->label_2->setText(message);
    }
    else if(message.startsWith("COMINFO:"))
    {
        QString temp;
        temp = message.right(4);
        if(!temp.startsWith("COM"))
            message = message.right(5);
        else
            message = message.right(4);

        this->close();
       /* QString textview;
        textview += "程序初始化中...";
        char *text = textview.toLatin1().data();

        ui->label_2->setText("程序初始化中");*/

        thread->exit();
        wt = new MainApplicationUI(message, NULL);
        wt->setFixedSize(357,618);
        wt->show();
        wt->setWindowTitle("物联网创新设计");
        this->close();
    }
    else
    {
        ui->label_2->setText(message);
    }

}
