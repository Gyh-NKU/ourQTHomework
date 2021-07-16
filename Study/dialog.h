#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QTime>

class LearnData{
public:
    QString title;
    QString details;
    QDate time;
    LearnData(QString t,QString de,QDate time):title(t),details(de),time(time){

    }

    LearnData()=default;
};
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    LearnData getinput();
    void setContents(const QString& title, const QString& details, const QDate& date);
    ~Dialog();

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
