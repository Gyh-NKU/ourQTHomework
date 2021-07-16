#include "usefultools.h"
#include "ui_usefultools.h"
#include "cal_widget.h"

UsefulTools::UsefulTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsefulTools)
{
    ui->setupUi(this);
    QImage _image;
    _image.load("://imgs/beauty_8.jpg");
    setAutoFillBackground(true);   // 这个属性一定要设置
     QPalette pal(palette());
      pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                        Qt::SmoothTransformation)));
     setPalette(pal);
     setWindowTitle("实用工具");
     Cal_Widget * cw = new Cal_Widget;
     connect(ui->toolButton,&QToolButton::clicked,[=]{
        this->hide();
         cw->show();
     });
     connect(cw,&Cal_Widget::hasclosed,this,[=]{
         show();
     });

}

UsefulTools::~UsefulTools()
{
    delete ui;
}
void UsefulTools::closeEvent(QCloseEvent *){
    emit hasclosed();
}
