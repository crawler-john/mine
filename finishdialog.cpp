#include "finishdialog.h"
#include "ui_finishdialog.h"

finishDialog::finishDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finishDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setFixedWidth(40);

    connect(ui->pushButton_again,SIGNAL(clicked()),this,SLOT(gameAgainButton()));
    connect(ui->pushButton_exit,SIGNAL(clicked()),this,SLOT(gameExitButton()));


}

finishDialog::~finishDialog()
{
    delete ui;
}

void finishDialog::setGameOverTime(int t_time)
{
    qDebug() << "1111111111111111111111";
    //把int型的数据装换为Qstring
    char buf[10];
    itoa(t_time, buf, 10);
    QString t_timeStr = QString(buf);
    qDebug() << t_timeStr;
    ui->lineEdit->setText(t_timeStr);
    ui->lineEdit->setDisabled(true);
}


void finishDialog::gameAgainButton()
{
    sndGameAgain();
    this->close();
}

void finishDialog::gameExitButton()
{
    sndExitGAME();
    this->close();
}

