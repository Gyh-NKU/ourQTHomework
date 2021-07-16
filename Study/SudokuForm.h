#ifndef SUDOKU_FORM_H
#define SUDOKU_FORM_H

#include <QWidget>
#include <QPushButton>
#include "SudokuWidget.h"

namespace Ui {
class SudokuForm;
}
class NumTableWidget;

class SudokuForm : public QDialog
{
    Q_OBJECT

public:
    explicit SudokuForm(QPoint point, QWidget *parent = 0,NumTableWidget* widget=0, int row=0, int col=0);
    ~SudokuForm();

private slots:
      void on_clearNumBtn_clicked();

private:
    Ui::SudokuForm *ui;
    QPushButton _btn[9];
    NumTableWidget* _wid;
    int _row,_col;
    QPoint _point;
};

#endif // SUDOKU_FORM_H
