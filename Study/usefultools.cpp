#include "usefultools.h"
#include "ui_usefultools.h"

UsefulTools::UsefulTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsefulTools)
{
    ui->setupUi(this);
}

UsefulTools::~UsefulTools()
{
    delete ui;
}
void UsefulTools::closeEvent(QCloseEvent *){
    emit hasclosed();
}
