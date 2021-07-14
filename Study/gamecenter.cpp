#include "gamecenter.h"
#include "ui_gamecenter.h"
#include "widget.h"

GameCenter::GameCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameCenter)
{
    ui->setupUi(this);
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
}

GameCenter::~GameCenter()
{
    delete ui;
}

void GameCenter::closeEvent(QCloseEvent *event){
    emit hasclosed();
}
