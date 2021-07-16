#ifndef SUDOKU_WIDGET_H
#define SUDOKU_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCloseEvent>
#include "SudokuForm.h"
namespace Ui {
class NumTableWidget;
}
class SudokuForm;

enum Type
{
    SHOWANSWER,
    CREATEENIGMA,
};

class NumTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NumTableWidget(QWidget *parent = 0);
    ~NumTableWidget();

    void setNum(int row, int col,int num);
    void clearNum(int row, int col);

protected:
    void process(bool show);

private slots:

    void on_showAnswerBtn_clicked();

    void on_createEnigmaBtn_clicked();

    void on_clearAllBtn_clicked();

    void closeEvent(QCloseEvent *) override;


private:
    Ui::NumTableWidget *ui;
    int _num[9][9];
    QPushButton _btn[9][9];
signals:
    void hasclosed();

};

#endif // SUDOKU_WIDGET_H
