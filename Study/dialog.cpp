#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

}

Dialog::~Dialog()
{
    delete ui;
}
LearnData Dialog::getinput(){
    QString a,b;
    QDate c;
    a=ui->lineEdit->text();
    b=ui->textEdit->toPlainText();
    c=ui->dateEdit->date();

    return LearnData(a,b,c);
}
void Dialog::setContents(const QString& title, const QString& details, const QDate& date){
    ui->dateEdit->setDate(date);
    ui->lineEdit->setText(title);
    ui->textEdit->setText(details);
}
