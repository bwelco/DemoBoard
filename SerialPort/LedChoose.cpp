#include "LedChoose.h"
#include "ui_LedChoose.h"


LedChoose::LedChoose(MainApplicationUI* s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LedChoose)
{
    ui->setupUi(this);
    this->standardItemModel = new QStandardItemModel(this);
    this->listView = this->ui->listView;
    QStringList strList;
    strList.append("无色(关闭)");
    strList.append("红色");
    strList.append("绿色");
    strList.append("蓝色");
    strList.append("青色");
    strList.append("黄色");
    strList.append("品红");
    strList.append("白色");

    int nCount = strList.size();
    for(int i = 0; i < nCount; i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        item->setSizeHint(QSize(item->sizeHint().width(), 40));
      /*  if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, Qt::darkGreen);
            linearGrad.setColorAt(1, Qt::yellow);
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }*/
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
        switch(i)
        {
            case 0:{
                 linearGrad.setColorAt(0, Qt::white);
                 QBrush brush(linearGrad);
                 item->setBackground(brush);
                 break;
            }
            case 1:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::red);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 2:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::green);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 3:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::blue);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 4:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::cyan);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 5:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::yellow);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 6:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::magenta);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
            case 7:{
                     QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                     linearGrad.setColorAt(0, Qt::white);
                     QBrush brush(linearGrad);
                     item->setBackground(brush);
                     break;
            }
        }

        standardItemModel->appendRow(item);
    }
    listView->setModel(standardItemModel);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
    connect(this, SIGNAL(choose(int)),s, SLOT(LedChooseResult(int)));
}

LedChoose::~LedChoose()
{
    delete ui;
}

void LedChoose::itemClicked(QModelIndex index)
{
    //qDebug() << index.row();
    emit this->choose(index.row());
    this->close();
}
