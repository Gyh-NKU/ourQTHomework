#include "gamecenter.h"
#include "ui_gamecenter.h"
#include "widget.h"
#include "SudokuWidget.h"
#include<QImage>
#include<QPalette>

GameCenter::GameCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameCenter)
{
    ui->setupUi(this);
    QImage _image;
    _image.load("://imgs/cartoon.jpg");
    setAutoFillBackground(true);   // 这个属性一定要设置
     QPalette pal(palette());
      pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                        Qt::SmoothTransformation)));
     setPalette(pal);
    Widget * wid = new Widget;
    connect(ui->toolButton,&QToolButton::clicked,[=](){
        this->hide();
        wid->show();
    });
    QDesktopWidget *desktop=new QDesktopWidget;
    connect(wid,&Widget::hasclosed,[=](){
      move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
      show();
    });
    NumTableWidget * ntw = new NumTableWidget;
    connect(ui->toolButton_2,&QToolButton::clicked,[=](){
        this->hide();
        ntw->show();
    });
    connect(ntw,&NumTableWidget::hasclosed,[=](){
        move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
        show();
    });
}

GameCenter::~GameCenter()
{
    delete ui;
}

void GameCenter::closeEvent(QCloseEvent *){
    emit hasclosed();
}
