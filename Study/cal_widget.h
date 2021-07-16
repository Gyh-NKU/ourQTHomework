#ifndef CAL_WIDGET_H
#define CAL_WIDGET_H

#include <QWidget>
#include <QStack>
#include <QKeyEvent>
#include <QCloseEvent>
namespace Ui {
class Cal_Widget;
}

class Cal_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Cal_Widget(QWidget *parent = 0);
    ~Cal_Widget();
    void getChar();//将QString转换为QByteArray
    void getSuffix();//获取后缀表达式
    void CalculateSuffix();//计算后缀表达式
    void initialize();//初始化


private slots:
    void number_0();
    void number_1();
    void number_2();
    void number_3();
    void number_4();
    void number_5();
    void number_6();
    void number_7();
    void number_8();
    void number_9();

    void sign_equal();
    void sign_plus();
    void sign_minus();
    void sign_mutiply();
    void sign_divide();
    void sign_bracket_l();
    void sign_bracket_r();
    void sign_point();

    void function_C();
    void function_CE();
private:
    Ui::Cal_Widget *ui;
    QString Input;//输入的表达式
    QVector<QString> Output;//后缀表达式
    QByteArray ba;//输入表达式转换为字节数组
    QStack<char> s1;//中缀表达式转换为后缀表达式时用到的栈
    QStack<float> s2;//后缀表达式计算结果时用到的栈
    float result;//计算结果
    bool cal_leagal = true;
    int situation = 0;
    void keyPressEvent(QKeyEvent * event) override;
    void closeEvent(QCloseEvent *) override;

signals:
    void hasclosed();

};

#endif // WIDGET_H
