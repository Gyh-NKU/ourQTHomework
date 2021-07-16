#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_plan.h"
#include "gamecenter.h"
#include "usefultools.h"
#include <QToolButton>
#include <QDesktopWidget>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage _image;
     _image.load("://imgs/bk.jpg");
     setAutoFillBackground(true);   // 这个属性一定要设置
      QPalette pal(palette());
       pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)));
      setPalette(pal);
//    QImage _image;
//     _image.load("://imgs/jiege.jpg");
//     setAutoFillBackground(true);   // 这个属性一定要设置
//      QPalette pal(palette());
//       pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
//                         Qt::SmoothTransformation)));
//       setPalette(pal);
    QDesktopWidget *desktop = qApp->desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    Add_Plan * adp = new Add_Plan;
    GameCenter * gc= new GameCenter;
    UsefulTools * ut= new UsefulTools;
    //连接按钮打开事件
//    connect(ui->tbtn1,&QToolButton::clicked,[=](){
//        this->hide();
//        tdp->show();

//    });
//    connect(ui->tbtn2,&QToolButton::clicked,[=](){
//        this->hide();
//        dlp->show();

//    });
    connect(ui->tbtn3,&QToolButton::clicked,[=](){
        this->hide();
        adp->show();

    });
    connect(ui->tbtn4,&QToolButton::clicked,this,[=](){
        if(QMessageBox::question(this,"确认退出吗？","确认退出吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes){
                close();
        }
    });
    connect(ui->tbtn2,&QToolButton::clicked,[=](){
        this->hide();
        gc->show();
    });
    connect(ui->tbtn,&QToolButton::clicked,[=](){
        this->hide();
        ut->show();
    });

    //连接二级页面返回事件
//    connect(tdp,&Today_Plan::hasclosed,this,[=](){

//        move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
//        show();
//    });
//    connect(dlp,&Daily_Plan::hasclosed,this,[=](){
//        move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
//        show();
//    });
    connect(adp,&Add_Plan::hasclosed,[=](){
      move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
      show();
    });
    connect(gc,&GameCenter::hasclosed,[=](){
      move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
      show();
    });
    connect(ut,&UsefulTools::hasclosed,[=](){
      move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
      show();
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

