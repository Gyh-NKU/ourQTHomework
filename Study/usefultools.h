#ifndef USEFULTOOLS_H
#define USEFULTOOLS_H

#include <QWidget>

namespace Ui {
class UsefulTools;
}

class UsefulTools : public QWidget
{
    Q_OBJECT

public:
    explicit UsefulTools(QWidget *parent = nullptr);
    ~UsefulTools();
    void closeEvent(QCloseEvent *) override;

private:
    Ui::UsefulTools *ui;
signals:
    void hasclosed();
};

#endif // USEFULTOOLS_H
