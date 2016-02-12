#include "SearchForSerialPort.h"
#include "MainApplicationUI.h"
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QWidget>

/*
    Author: MoreFree
    截至2016年2月8日 18:31:47: 1620行(不连界面文件)
    项目开始于2016年1月25日
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SearchForSerialPort wt;
    wt.setWindowTitle("连接中...");
    wt.show();

    return a.exec();
}
