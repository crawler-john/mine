#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"

statisticsDialog::statisticsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statisticsDialog),m_recordPrimary(QString("0")),m_recordMiddle(QString("0")),m_recordHigh(QString("0"))
{
    ui->setupUi(this);
    ui->label_primary->setFixedWidth(30);
    ui->label_middle->setFixedWidth(30);
    ui->label_high->setFixedWidth(30);
    ui->lineEdit_primary->setFixedWidth(50);
    ui->lineEdit_middle->setFixedWidth(50);
    ui->lineEdit_high->setFixedWidth(50);
    ui->lineEdit_primary->setDisabled(true);
    ui->lineEdit_middle->setDisabled(true);
    ui->lineEdit_high->setDisabled(true);
    this->setWindowTitle("扫雷统计");
    this->setWindowIcon(QIcon(":/images/statistics.ico"));
    connect(ui->pushButton_OK,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(clearRecord()));
}

statisticsDialog::~statisticsDialog()
{
    delete ui;
}
//打开统计文件并读取数据到
void statisticsDialog::openStatisticsFile()
{

    QFile t_readFile("./record.txt");
    t_readFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!t_readFile.isOpen())
    {
        qDebug() << "打开文件失败";
        QFile t_writeFile("./record.txt");
        t_writeFile.open(QIODevice::WriteOnly|QIODevice::Text);
        if(!t_writeFile.isOpen())
        {
            qDebug()  << "打开文件失败并且重写文件失败";
            return;
        }
        QTextStream t_textstreamwrite(&t_writeFile);
        t_textstreamwrite << m_recordPrimary << " " << m_recordMiddle << " " << m_recordHigh;
        t_writeFile.close();

        t_readFile.open(QIODevice::ReadOnly|QIODevice::Text);
        if(!t_readFile.isOpen())
        {
            qDebug() << "再错可以去死了";
            return;
        }
    }
    QTextStream t_textstream(&t_readFile);

    QString t_allRecord = t_textstream.readAll();

    //将读取到的数据按照中间的空格分成三个
    m_recordPrimary = t_allRecord.split(" ")[0];
    m_recordMiddle = t_allRecord.split(" ")[1];
    m_recordHigh = t_allRecord.split(" ")[2];

    ui->lineEdit_primary->setText(m_recordPrimary);
    ui->lineEdit_middle->setText(m_recordMiddle);
    ui->lineEdit_high->setText(m_recordHigh);
    qDebug() << m_recordPrimary << m_recordMiddle << m_recordHigh;


    t_readFile.close();

}
//刷新记录调用的函数
void statisticsDialog::refreshRecond(statisticsDialog::Record t_record, int t_recordTime)
{
    //将游戏成功是时间转换成qstring类型
    char buf[10] = {};
    QString t_str = QString(itoa(t_recordTime,buf,10));

    switch(t_record)
    {
    case PRIMARY:
    {
        //初级记录时间
        int t_primary = m_recordPrimary.toInt();
        if(t_recordTime < t_primary || t_primary == 0)
        {
            qDebug() << "新的成功时间" << t_str << "原来的时间" << t_primary;
            m_recordPrimary = t_str;
            ui->lineEdit_primary->setText(m_recordPrimary);
        }
    }

        break;
    case MIDDLE:
    {
        int t_middle = m_recordMiddle.toInt();
        if(t_recordTime < t_middle || t_middle == 0)
        {
            m_recordMiddle = t_str;
            ui->lineEdit_middle->setText(m_recordMiddle);
        }
    }

        break;
    case HIGH:
    {
        int t_hign = m_recordHigh.toInt();
        if(t_recordTime < t_hign || t_hign == 0)
        {
            m_recordHigh = t_str;
            ui->lineEdit_high->setText(m_recordHigh);
        }
        break;
    }

    }
    //将文件的数据更新
    QFile t_writeFile("./record.txt");
    t_writeFile.open(QIODevice::WriteOnly|QIODevice::Text);
    if(!t_writeFile.isOpen())
    {
        qDebug()  << "打开保存文件失败";
        return;
    }
    QTextStream t_textstreamwrite(&t_writeFile);
    t_textstreamwrite << m_recordPrimary << " " << m_recordMiddle << " " << m_recordHigh;
    t_writeFile.close();
}

void statisticsDialog::clearRecord()
{
    m_recordPrimary = "0";
    m_recordMiddle = "0";
    m_recordHigh = "0";
    //保存
    QFile t_writeFile("./record.txt");
    t_writeFile.open(QIODevice::WriteOnly|QIODevice::Text);
    if(!t_writeFile.isOpen())
    {
        qDebug()  << "打开保存文件失败";
        return;
    }
    QTextStream t_textstreamwrite(&t_writeFile);
    t_textstreamwrite << m_recordPrimary << " " << m_recordMiddle << " " << m_recordHigh;
    t_writeFile.close();
    ui->lineEdit_primary->setText(m_recordPrimary);
    ui->lineEdit_middle->setText(m_recordMiddle);
    ui->lineEdit_high->setText(m_recordHigh);
}


