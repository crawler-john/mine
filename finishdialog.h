#ifndef FINISHDIALOG_H
#define FINISHDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class finishDialog;
}

class finishDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit finishDialog(QWidget *parent = 0);
    ~finishDialog();
    
    //设置结束时间的函数
    void setGameOverTime(int t_time);

private:
    Ui::finishDialog *ui;
signals:
    //再来一次信号
    void sndGameAgain();
    //退出信号
    void sndExitGAME();
public slots:
    void gameAgainButton();

    void gameExitButton();

};

#endif // FINISHDIALOG_H
