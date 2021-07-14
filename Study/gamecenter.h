#ifndef GAMECENTER_H
#define GAMECENTER_H

#include <QWidget>
#include<QDesktopWidget>
#include<QCloseEvent>

namespace Ui {
class GameCenter;
}

class GameCenter : public QWidget
{
    Q_OBJECT

public:
    explicit GameCenter(QWidget *parent = nullptr);
    ~GameCenter();
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::GameCenter *ui;
signals:
    void hasclosed();
};

#endif // GAMECENTER_H
