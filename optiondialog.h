#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();

    //是否播放声音
    bool m_soundPlay;
    
private:
    Ui::OptionDialog *ui;

signals:
    //发送游戏的宽度，长度，雷数
    void sndGameInfo(int t_x,int t_y,int t_mineNum);

public slots:
    //处理窗口显示
    void editlinedDsplay(bool t_result);
    //处理最下面的按键盒子
    void disposebuttonBox();
    //处理最下面按键盒子的退出按钮
    void disposeButtonExit();
};

#endif // OPTIONDIALOG_H
