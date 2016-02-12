#ifndef SEARCHFORSERIALPORT_H
#define SEARCHFORSERIALPORT_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include "SerialThread.h"
#include "ui_SearchForSerialPort.h"

namespace Ui {
class SearchForSerialPort;
}
class SerialThread;

class SearchForSerialPort : public QWidget
{
    Q_OBJECT

public:
    enum RETCODE
    {
        OPENFAIL = 0,
        BAUDFAIL = 1,
        DATE8FAIL = 2,
        NoParityFAIL = 3,
        ONESTOPFAIL = 4,
        NoFlowControlFAIL = 5,
        ReadWriteFail = 6,
        OPENSUCCESS = 7
    };
    explicit SearchForSerialPort(QWidget *parent = 0);
    ~SearchForSerialPort();
    int TimberCount = 0;
    SerialThread *thread;


private:
    Ui::SearchForSerialPort *ui;
    QSerialPort *my_serialport;
    QListView *listView2;
    QStandardItemModel *standardItemModel;
    QStringList* strList;
    QStringList *comlist;
    QTimer* timer;
    MainApplicationUI *wt;
signals:

private slots:
     void itemClicked();
     void printf(QString text);
     void updateUI();
     void RecvUI(QString message);
};

#endif // SEARCHFORSERIALPORT_H
