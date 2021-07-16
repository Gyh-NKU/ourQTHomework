#include "cal_widget.h"
#include "ui_cal_widget.h"
#include <QDebug>
#include <iostream>

Cal_Widget::Cal_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cal_Widget)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->move(QPoint(0,0));
    ui->lineEdit->setAlignment(Qt::AlignRight);
    setWindowTitle(QString("计算器"));
    //设置各按钮事件
    connect(ui->btn_0, &QPushButton::clicked, this, &Cal_Widget::number_0);
    connect(ui->btn_1, &QPushButton::clicked, this, &Cal_Widget::number_1);
    connect(ui->btn_2, &QPushButton::clicked, this, &Cal_Widget::number_2);
    connect(ui->btn_3, &QPushButton::clicked, this, &Cal_Widget::number_3);
    connect(ui->btn_4, &QPushButton::clicked, this, &Cal_Widget::number_4);
    connect(ui->btn_5, &QPushButton::clicked, this, &Cal_Widget::number_5);
    connect(ui->btn_6, &QPushButton::clicked, this, &Cal_Widget::number_6);
    connect(ui->btn_7, &QPushButton::clicked, this, &Cal_Widget::number_7);
    connect(ui->btn_8, &QPushButton::clicked, this, &Cal_Widget::number_8);
    connect(ui->btn_9, &QPushButton::clicked, this, &Cal_Widget::number_9);

    connect(ui->btn_equal, &QPushButton::clicked, this, &Cal_Widget::sign_equal);
    connect(ui->btn_plus, &QPushButton::clicked, this, &Cal_Widget::sign_plus);
    connect(ui->btn_minus, &QPushButton::clicked, this, &Cal_Widget::sign_minus);
    connect(ui->btn_mutiply, &QPushButton::clicked, this, &Cal_Widget::sign_mutiply);
    connect(ui->btn_divide, &QPushButton::clicked, this, &Cal_Widget::sign_divide);
    connect(ui->btn_point, &QPushButton::clicked, this, &Cal_Widget::sign_point);
    connect(ui->btn_bracket_l, &QPushButton::clicked, this, &Cal_Widget::sign_bracket_l);
    connect(ui->btn_bracket_r, &QPushButton::clicked, this, &Cal_Widget::sign_bracket_r);

    connect(ui->btn_clear, &QPushButton::clicked, this, &Cal_Widget::function_C);
    connect(ui->btn_cancel, &QPushButton::clicked, this, &Cal_Widget::function_CE);
}

Cal_Widget::~Cal_Widget() {
    delete ui;
}

void Cal_Widget::getChar() {//
    ba = Input.toLatin1();
}

//下面函数将中序表达式转化成后序表达式
//算法如下
//此时用到的栈起辅助作用
//1.遇到数字直接输出
//2.遇见非数字时, 如果堆栈为空，则直接把该字符放入堆栈
//3.当堆栈不非空时,如果是+或- 那么遍历堆栈栈顶元素 一直输出优先级>=加减的 即输出栈顶的+或-或*或/,即除了小括号以外的内容,
//当遇到其他字符时（左括号）时,或者堆栈空时结束此过程
//4.如果是*或/ 那么遍历堆栈栈顶元素 一直输出优先级>=乘除的 即输出栈顶的*或/,
//当遇到其他字符时（如左括号，减号，除号）或堆栈空时break
//5.如果该字符是右括号时，一直输出栈顶元素，直到遇见左括号为止break:
//6.如果该字符是左括号时，直接放入堆栈
//7.遍历完字符串后不断弹出并输出堆栈内元素直到栈空
//本函数中的“输出”为扩展一个字符串
void Cal_Widget::getSuffix() {
  for(int i = 0; i < ba.size(); i++) {
      //步骤1（此处用到了小数处理，即将小数点看做数的一部分进行输出）
      if((ba[i] >= '0' && ba[i] <= '9') || ba[i] == '.') {
         QString str;
         QByteArray m;
         for(; (ba[i] >= '0' && ba[i] <= '9') || ba[i] == '.'; i++) {
             m.append(ba[i]);//将一个数字存储到字节数组m中
         }
         Output.append(QString(m));//将字节数组m转换为QString，并将字符串输出
         i--;
      }
      //步骤2
      else if(s1.isEmpty()) {
          s1.push(ba[i]);
      }//步骤3
      else if(ba[i] == '+' || ba[i] == '-') {

          while(!s1.empty()) {
              if(s1.top() == '+' || s1.top() == '-' || s1.top() == '*' || s1.top() == '/') {
                  Output.append(QString(s1.pop()));//把字符转换为字符串输出
//                QString str = QString(s1.pop());
//                Output.append(str);
               }else break;
          }
          s1.push(ba[i]);
      }//步骤4
      else if(ba[i] == '*' || ba[i] == '/') {

          while(!s1.empty()) {
              if(s1.top() == '*' || s1.top() == '/') {
                  //把字符转换为字符串输出
                  Output.append(QString(s1.pop()));
               }else break;
          }
          s1.push(ba[i]);
      }//步骤5
      else if(ba[i] == ')') {
          while(!s1.empty()) {
              if(s1.top() == '(') {
                  s1.pop();
                  break;
              }//把字符转换为字符串输出
              Output.append(QString(s1.pop()));
          }
      }//步骤6
      else if(ba[i] == '(') {
          s1.push(ba[i]);
      }
  }
  //步骤7
  while(!s1.empty()) {
      Output.append(QString(s1.pop()));
  }
  //输出后缀表达式，以进行检验
  qDebug() << Output;
}

//下面函数是根据后序表达式计算结果
//1.如果是数字，直接入栈
//2.如果是运算符，弹栈两次，并进行运算，运算后，结果入栈

void Cal_Widget::CalculateSuffix() {
  for(int i = 0; i < Output.size(); i++) {
      if (situation == 2) break;
      else {
          bool is_Num = true;
          Output[i].toFloat(&is_Num);
          if(is_Num) {
              s2.push(Output[i].toFloat(&is_Num));
          }else if(Output[i] == "+" || Output[i] == "-" || Output[i] == "*" || Output[i] == "/") {
              float x = s2.pop();
              float y = s2.pop();
              if(Output[i] == "+") s2.push(y + x);
              else if(Output[i] == "-") s2.push(y - x);
              else if(Output[i] == "*") s2.push(y * x);
              else if(Output[i] == "/") {
                  if (x == 0) situation = 2;
                  else s2.push(y / x);
              }
          }
      }
  }
  if (situation == 0) {
      result = s2.pop();
      qDebug() << result;
  }
}

void Cal_Widget::initialize() {
    ba.clear();
    Output.clear();
}

void Cal_Widget::sign_equal() {
    Input = ui->lineEdit->text();//获取表达式
    getChar();
    getSuffix();
    CalculateSuffix();
    ui->lineEdit->clear();//清空文本编辑框
    if(situation == 0) {
        ui->lineEdit->setText(QString::number(result));
    }else if (situation == 2){
        ui->lineEdit->setText("ERR");
    }
    initialize();
    situation = 1;
}

void Cal_Widget::number_0() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "0";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("0");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_1() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "1";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("1");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_2() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "2";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("2");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_3() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "3";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("3");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_4() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "4";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("4");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_5() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "5";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("5");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_6() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "6";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("6");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_7() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "7";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("7");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_8() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "8";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("8");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::number_9() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = "9";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append("9");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::sign_plus() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append("+");
    ui->lineEdit->setText(str);
}

void Cal_Widget::sign_minus() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append("-");
    ui->lineEdit->setText(str);
}

void Cal_Widget::sign_mutiply() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append("*");
    ui->lineEdit->setText(str);
}

void Cal_Widget::sign_divide() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append("/");
    ui->lineEdit->setText(str);
}

void Cal_Widget::sign_point() {
    if (situation == 1) {
        situation = 0;
        ui->lineEdit->clear();
        QString str = ".";
        ui->lineEdit->setText(str);
    }
    else {
        QString str = ui->lineEdit->text();
        str.append(".");
        ui->lineEdit->setText(str);
    }
}

void Cal_Widget::sign_bracket_l() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append("(");
    ui->lineEdit->setText(str);
}

void Cal_Widget::sign_bracket_r() {
    if(situation == 1) situation = 0;
    QString str = ui->lineEdit->text();
    str.append(")");
    ui->lineEdit->setText(str);
}

void Cal_Widget::function_C() {//清空所有内容，并初始化
    ui->lineEdit->clear();
    initialize();
    situation = 0;
}

void Cal_Widget::function_CE() {//退格删除一个字符
    QString str = ui->lineEdit->text();
    if(str == "ERR") ui->lineEdit->clear();
    else ui->lineEdit->backspace();
}
void Cal_Widget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_0:
        number_0();
        break;
    case Qt::Key_1:
        number_1();
        break;
    case Qt::Key_2:
        number_2();
        break;
    case Qt::Key_3:
        number_3();
        break;
    case Qt::Key_4:
        number_4();
        break;
    case Qt::Key_5:
        number_5();
        break;
    case Qt::Key_6:
        number_6();
        break;
    case Qt::Key_7:
        number_7();
        break;
    case Qt::Key_8:
        number_8();
        break;
    case Qt::Key_9:
        number_9();
        break;
    case Qt::Key_Plus:
        sign_plus();
        break;
    case Qt::Key_Minus:
        sign_minus();
        break;
    case Qt::Key_Asterisk:
        sign_mutiply();
        break;
    case Qt::Key_Slash:
        sign_divide();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        sign_equal();
        break;
    case Qt::Key_ParenLeft:
        sign_bracket_l();
        break;
    case Qt::Key_ParenRight:
        sign_bracket_r();
        break;
    case Qt::Key_Backspace:
        function_CE();
        break;



    default:
        qDebug() << event->key();
        break;
    }
}
void Cal_Widget::closeEvent(QCloseEvent *){
    emit hasclosed();
}
