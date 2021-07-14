#ifndef ADD_PLAN_H
#define ADD_PLAN_H

#include <QWidget>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QModelIndex>
#include <QDialog>
#include <QComboBox>
#include "dialog.h"


namespace Ui {
class Add_Plan;
}

class Add_Plan : public QWidget
{
    Q_OBJECT

public:
    explicit Add_Plan(QWidget *parent = nullptr);
    ~Add_Plan();
    void closeEvent(QCloseEvent*);
    void setRemind();
    void addComboBox();
private:
    Ui::Add_Plan *ui;
    QSqlDatabase db;
    QSqlQuery * query;
    QSqlQueryModel * qmodel;
    QSqlQueryModel * qmodel2;
    QModelIndex index;
    QString curPlanName;
    QString curPlanDetails;
    QString curTime;

signals:
    void hasclosed();
};



#endif // ADD_PLAN_H
