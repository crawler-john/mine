#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>

namespace Ui {
class statisticsDialog;
}

class statisticsDialog : public QDialog
{
    Q_OBJECT
public:
    enum Record
    {
        PRIMARY = 1,
        MIDDLE = 2,
        HIGH =3
    };
    
public:
    explicit statisticsDialog(QWidget *parent = 0);
    ~statisticsDialog();
    
private:
    Ui::statisticsDialog *ui;

private:
    QString m_recordPrimary; //初级记录
    QString m_recordMiddle;  //中级记录
    QString m_recordHigh;    //高级记录


public:
    //打开统计文件
    void openStatisticsFile();
    //刷新记录
    void refreshRecond(Record t_record,int t_recordTime);
public slots:
    //清空数据
    void clearRecord();

};

#endif // STATISTICSDIALOG_H
