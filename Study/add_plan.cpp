#include "add_plan.h"
#include "ui_add_plan.h"
#include <QDesktopWidget>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QComboBox>
#include <QCalendarWidget>
#include <QImage>
#include <QPalette>
Add_Plan::Add_Plan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_Plan)
{

    ui->setupUi(this);
    QImage _image;
     _image.load("://imgs/logo.png");
     setAutoFillBackground(true);   // 这个属性一定要设置
      QPalette pal(palette());
       pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)));
      setPalette(pal);
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("learn.db");
    db.open();
    query = new QSqlQuery;
    query->exec("create table planinfo(planname,plandetails,time)");
    qmodel=new QSqlQueryModel;
    qmodel->setQuery("select planname as 任务名称,time as 创建时间,plandetails as 任务内容 from planinfo");
    ui->tableView->setModel(qmodel);
    qmodel2=new QSqlQueryModel;
    qmodel2->setQuery("select planname as 任务名称,time as 创建时间,plandetails as 任务内容 from planinfo where time='"+QDate::currentDate().toString("yyyy-MM-dd")+"'");
    ui->tableView_2->setModel(qmodel2);
    ui->stackwidget->setCurrentIndex(0);
    connect(ui->btn_addpage,&QPushButton::clicked,[=](){
        ui->stackwidget->setCurrentIndex(2);

    });
    connect(ui->btn_dailypage,&QPushButton::clicked,[=](){
        ui->stackwidget->setCurrentIndex(1);
    });
    connect(ui->btn_todaypage,&QPushButton::clicked,[=](){
        ui->stackwidget->setCurrentIndex(0);
        addComboBox();
    });
    //添加
    connect(ui->btn_add,&QPushButton::clicked,[=](){
        Dialog dialog;
        if(dialog.exec()==QDialog::Accepted){
            LearnData data;
            data=dialog.getinput();
            //qDebug() << data.time;
            bool flag=1;
            for(int i=0;i<ui->tableView->model()->rowCount();i++){
                if(ui->tableView->model()->index(i,0).data().toString()==data.title){
                    flag=0;
                    break;
                }
            }
            if(flag){
                QString sql="insert into planinfo(planname,plandetails,time) values('"+data.title+"','"+data.details+"','"+data.time.toString("yyyy-MM-dd")+"')";
                query->exec(sql);
                qmodel->setQuery("select planname as 任务名称,time as 创建时间,plandetails as 任务内容 from planinfo");
                setRemind();
            }
            else{
                QMessageBox::critical(this,"添加失败","已存在同名内容");
            }
        }


    });
    //删除
    connect(ui->btn_del,&QPushButton::clicked,[=](){
        if(QMessageBox::question(this,"确认删除吗？","确认删除吗？")==QMessageBox::Yes){
            QString sql="delete from planinfo where planname='"+curPlanName+"'" ;
            QString sql2="delete from planremind where planname='"+curPlanName+"'" ;
            query->exec(sql);
            query->exec(sql2);
            qmodel->setQuery("select planname as 任务名称,time as 创建时间,plandetails as 任务内容 from planinfo");
            ui->textBrowser->setText("<h1 align=center>请选择任务</h1>");
            setRemind();
        }

    });
    connect(ui->tableView,&QTableView::clicked,this,[=](const QModelIndex &index){
        this->index=index;
        curPlanName = index.siblingAtColumn(0).data().toString();
        curPlanDetails = index.siblingAtColumn(2).data().toString();
        curTime = index.siblingAtColumn(1).data().toString();
        ui->textBrowser->setText(    QObject::tr("<h1 align=center>%1</h1>"
                                                 "<p> <font size='4'>&nbsp;&nbsp;%2</font></p>"
                                                 "<p align=right>创建于：%3</p>"
                                                 ).arg(curPlanName).arg(curPlanDetails).arg(curTime));
    });
    //修改
    connect(ui->btn_change,&QPushButton::clicked,[=](){
        Dialog dialog;
        dialog.setContents(curPlanName,curPlanDetails,QDate::fromString(curTime));
        if(dialog.exec()==QDialog::Accepted){
            LearnData data;
            data=dialog.getinput();
            QString sql="update planinfo set planname='"+data.title+"',plandetails='"+data.details+"',time='"+data.time.toString("yyyy-MM-dd")+"' where planname='"+curPlanName+"'";
            QString sql2="delete from planremind where planname='"+curPlanName+"'" ;
            query->exec(sql);
            query->exec(sql2);
            qmodel->setQuery("select planname as 任务名称,time as 创建时间,plandetails as 任务内容 from planinfo");
            setRemind();
        }
    });
    //子窗口2
    //添加任务
    addComboBox();
    //显示任务
    void(QComboBox::*fp)(int)=&QComboBox::currentIndexChanged;
    connect(ui->comboBox,fp,this,[=](){
        query->exec("select * from planinfo where planname='"+ui->comboBox->currentText()+"'");
        query->next();
        QString curPlanName = query->value("planName").toString();
        QString curPlanDetails = query->value("planDetails").toString();
        QString curTime = query->value("time").toDate().toString("yyyy-MM-dd");

//        qDebug() <<query->value("planname").toString();
        ui->textBrowser_2->setText(    QObject::tr("<h1 align=center>%1</h1>"
                                                 "<p> <font size='4'>&nbsp;&nbsp;%2</font></p>"
                                                 "<p align=right>创建于：%3</p>"
                                                 ).arg(curPlanName).arg(curPlanDetails).arg(curTime));
    });
    void(QComboBox::*fp2)(int)=&QComboBox::activated;
    connect(ui->comboBox,fp2,this,[=](){
        query->exec("select * from planinfo where planname='"+ui->comboBox->currentText()+"'");
        query->next();
        QString curPlanName = query->value("planName").toString();
        QString curPlanDetails = query->value("planDetails").toString();
        QString curTime = query->value("time").toDate().toString("yyyy-MM-dd");

//        qDebug() <<query->value("planname").toString();
        ui->textBrowser_2->setText(    QObject::tr("<h1 align=center>%1</h1>"
                                                 "<p> <font size='4'>&nbsp;&nbsp;%2</font></p>"
                                                 "<p align=right>创建于：%3</p>"
                                                 ).arg(curPlanName).arg(curPlanDetails).arg(curTime));
    });
    connect(ui->btn_delay,&QPushButton::clicked,[=](){
       if(QMessageBox::question(this,"确认推迟吗？","确认推迟吗？")==QMessageBox::Yes){
           query->exec("select * from planinfo where planname='"+ui->comboBox->currentText()+"'");
           query->next();
           QString curPlanName = query->value("planName").toString();
           QString curPlanDetails = query->value("planDetails").toString();
           QString curTime = query->value("time").toDate().toString("yyyy-MM-dd");
           query->exec("insert OR IGNORE into planremind(planname,plandetails,time,createtime) values('"+curPlanName+"','"+curPlanDetails+"','"+QDate::currentDate().addDays(1).toString("yyyy-MM-dd")+"','"+curTime+"') ");
       };
    });
    //子窗口3

    connect(ui->calendarWidget,&QCalendarWidget::clicked,[=](const QDate& date){
        qmodel2->setQuery("select planname as 任务名称,createtime as 创建时间,plandetails as 任务内容 from planremind where time='"+date.toString("yyyy-MM-dd")+"'");
        qDebug()<<date;
    });
    connect(ui->tableView_2,&QTableView::clicked,this,[=](const QModelIndex &index){
        this->index=index;
        curPlanName = index.siblingAtColumn(0).data().toString();
        curPlanDetails = index.siblingAtColumn(2).data().toString();
        curTime = index.siblingAtColumn(1).data().toString();
        ui->textBrowser_3->setText(    QObject::tr("<h1 align=center>%1</h1>"
                                                 "<p> <font size='4'>&nbsp;&nbsp;%2</font></p>"
                                                 "<p align=right>创建于：%3</p>"
                                                 ).arg(curPlanName).arg(curPlanDetails).arg(curTime));
    });


    //设置返回按钮
    connect(ui->btn_back,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->btn_back2,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->btn_back3,&QPushButton::clicked,this,&QWidget::close);





}

void Add_Plan::addComboBox(){
    //为选择框添加内容
    query->exec("select * from planremind where time='"+QDate::currentDate().toString("yyyy-MM-dd")+"'");
         while (true == query->next()) {
             if(query->value("time").toString()==QDate::currentDate().toString("yyyy-MM-dd")){
                 if(ui->comboBox->findText(query->value("planname").toString())==-1)
                 ui->comboBox->addItem(query->value("planname").toString());
             }
         };
}

Add_Plan::~Add_Plan()
{

    delete ui;
}
void Add_Plan::closeEvent(QCloseEvent*){
    setRemind();
    QSqlDatabase::removeDatabase("QSQLITE");
    emit hasclosed();

}
void Add_Plan::setRemind(){
    query->exec("create table planremind(planname,plandetails,time,createtime,primary key(planname,plandetails,time,createtime))");
    for(int i=0;i<ui->tableView->model()->rowCount();i++){
        QString tit=ui->tableView->model()->index(i,0).data().toString();
        QString det=ui->tableView->model()->index(i,2).data().toString();
        QDate tim= QDate::fromString(ui->tableView->model()->index(i,1).data().toString(),"yyyy-MM-dd");
        int days[] = {0,1,3,7,15,30,90,180};
        QDate time[8];
        for(int i=0;i<8;i++){
            QDate tem=tim;
            time[i]=tem.addDays(days[i]);
            query->exec("insert OR IGNORE into planremind(planname,plandetails,time,createtime) values('"+tit+"','"+det+"','"+time[i].toString("yyyy-MM-dd")+"','"+tim.toString("yyyy-MM-dd")+"')");
        }

    }
}


