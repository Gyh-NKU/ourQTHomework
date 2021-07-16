#include "SudokuForm.h"
#include "ui_SudokuForm.h"

//form窗口的构造函数
SudokuForm::SudokuForm(QPoint point, QWidget *parent,NumTableWidget* widget, int row, int col) :
    QDialog(parent),_wid(widget),_row(row),_col(col),
    ui(new Ui::SudokuForm)
{
    ui->setupUi(this);
    this->setGeometry(point.x()+400,point.y(),this->width(),this->height());
    this->move(this->x()-this->width()/2,this->y()-this->height()/2);
    for(int i=0; i<9; i++)
    {
        _btn[i].setFixedSize(55,55);
        _btn[i].setStyleSheet("color:green");
        QFont font(nullptr,30);
        _btn[i].setFont(font);
        _btn[i].setText(QString::number(i+1));
        ui->gridLayout->addWidget(&_btn[i],i/3,i%3);
        connect(&_btn[i],&QPushButton::clicked,[this,i](){
            _wid->setNum(_row,_col,i); //将用户在小窗口点击的数字传给widget
            this->close();
        });
    }
}

SudokuForm::~SudokuForm()
{
    delete ui;
}

void SudokuForm::on_clearNumBtn_clicked()
{
    _wid->clearNum(_row,_col);
    this->close();
}
