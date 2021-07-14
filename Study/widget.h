#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTime>
#include<QPainter>
#include<QString>
#include<QKeyEvent>
#include<QMessageBox>
#include<QDebug>
#include<QCloseEvent>
#include<QShowEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent* );//给格子涂色
    void keyPressEvent(QKeyEvent* event);


    QPushButton *btn;//开始按钮
    int s[4][4];//创建一个四乘四的网格
    int score=0;//分数，初始值赋零
    bool state;//游戏状态 true正常 false退出
    //移动操作函数
    void PressUp();
    void PressDown();
    void PressLeft();
    void PressRight();
    void myRand();
    void closeEvent(QCloseEvent *) override;
    void showEvent(QShowEvent *) override;
    struct Ns{
        int i;
        int j;
    };


public slots:
    void slotStart();//开始槽函数


private:
    Ui::Widget *ui;
signals:
    void hasclosed();
};
#endif // WIDGET_H
