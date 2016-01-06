#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutdialog::aboutdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutdialog)
{
    ui->setupUi(this);

    qDebug() << "aboutdialog";
    this->setWindowTitle("关于扫雷");
    this->setWindowIcon(QIcon(":/images/about.ico"));
}

aboutdialog::~aboutdialog()
{
    delete ui;
}


