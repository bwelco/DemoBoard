#ifndef LEDCHOOSE_H
#define LEDCHOOSE_H

#include <QWidget>
#include <QBrush>
#include <QRadialGradient>
#include <QDebug>
#include <QStandardItemModel>
#include <QListView>
#include <QStringList>
#include "MainApplicationUI.h"

namespace Ui {
class LedChoose;
}

class LedChoose : public QWidget
{
    Q_OBJECT

public:
    explicit LedChoose(MainApplicationUI* s, QWidget *parent = 0);
    ~LedChoose();
    QStandardItemModel* standardItemModel;
    QListView *listView;

private:
    Ui::LedChoose *ui;
signals:
    void choose(int index);
private slots:
     void itemClicked(QModelIndex index);
};

#endif // LEDCHOOSE_H
