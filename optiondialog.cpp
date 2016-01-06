#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog),m_soundPlay(true)
{
    ui->setupUi(this);
    this->setWindowTitle("选项");
    this->setWindowIcon(QIcon(":/images/option.ico"));
    ui->lineEdit_height->setDisabled(true);
    ui->lineEdit_width->setDisabled(true);
    ui->lineEdit_mineNum->setDisabled(true);
    ui->radioButton_primary->setChecked(true);
    ui->checkBoxMusic->setChecked(true);

    connect(ui->radioButton_custom,SIGNAL(toggled(bool)),this,SLOT(editlinedDsplay(bool)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(disposebuttonBox()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(disposeButtonExit()));
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::editlinedDsplay(bool t_result)
{
    qDebug() << "editlinedDsplay";
    if(!ui->radioButton_custom->isChecked())
    {
        ui->lineEdit_height->setDisabled(true);
        ui->lineEdit_width->setDisabled(true);
        ui->lineEdit_mineNum->setDisabled(true);
    }
    else
    {
        ui->lineEdit_height->setEnabled(true);
        ui->lineEdit_width->setEnabled(true);
        ui->lineEdit_mineNum->setEnabled(true);
    }
}

void OptionDialog::disposebuttonBox()
{
        //设置声音
        m_soundPlay = ui->checkBoxMusic->isChecked() ? true : false;

        qDebug() << "disposebuttonBox";
        if(ui->radioButton_primary->isChecked())
        {
            //初级模式
            qDebug() << "sndGameInfo(9,9,10)";
            emit sndGameInfo(9,9,10);
            this->close();

        }
        else if(ui->radioButton_middle->isChecked())
        {   //中级模式
            qDebug() << "sndGameInfo(16,16,40)";
            emit sndGameInfo(16,16,40);
            this->close();

        }
        else if(ui->radioButton_high->isChecked())
        {//高级模式
            qDebug() << "sndGameInfo(30,16,99)";
            emit sndGameInfo(30,16,99);
            this->close();

        }
        else if(ui->radioButton_custom->isChecked())
        {
            //自定义模式
            qDebug() << "sndGameInfo(t_x,t_y,t_mineNum)";

            int t_x = ui->lineEdit_width->text().toInt();
            int t_y = ui->lineEdit_height->text().toInt();
            int t_mineNum = ui->lineEdit_mineNum->text().toInt();
            if((t_x >=9 && t_x <=30) &&(t_y>=9 && t_y <= 20) && (t_mineNum >=10 && t_mineNum <=588) && (t_x * t_y > t_mineNum))
            {

                emit sndGameInfo(t_x,t_y,t_mineNum);
                this->close();

            }
            else
            {
                QMessageBox::information(this,"提示","您输入的数字不在范围内,请重新输入!",QMessageBox::Ok);
            }


        }




}



void OptionDialog::disposeButtonExit()
{
    ui->checkBoxMusic->setChecked(m_soundPlay);
    this->close();
}
