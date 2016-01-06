#ifndef CARTOON_H
#define CARTOON_H

#include <QMainWindow>
#include <QGraphicsView>    //镜头类
#include "myscence.h"       //我的舞台类
#include "myitem.h"         //我的工具类
#include <stdlib.h>
#include <time.h>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>           //定时器类
#include <QSpacerItem>      //垫片类
#include <QMessageBox>
#include "optiondialog.h"
#include "aboutdialog.h"
#include "statisticsdialog.h"
#include "finishdialog.h"
#include <QSound>
#include <QDebug>


class cartoon : public QMainWindow
{
    Q_OBJECT
    
public:
    cartoon(QWidget *parent = 0);
    ~cartoon();



private:
    QMenu *m_gameMenu;  //游戏菜单
    QMenu *m_helpMenu;  //帮助菜单
    QAction *m_newGameAct1;   //新游戏
    QAction *m_statisticsInfoAct2;   //统计信息
    QAction *m_optionAct3;      //选项
    QAction *m_exitAct4;        //退出
    QAction *m_aboutAct;        //关于选型
    QWidget *m_centreWidget;    //中心窗体
    QVBoxLayout *m_vLayout; //垂直布局
    QHBoxLayout *m_hLayout; //水平布局
    QSpacerItem *m_spacer1; //垫片1
    QSpacerItem *m_spacer2; //垫片2
    QLCDNumber *m_lcdTime;  //时间LCD
    QLCDNumber *m_lcdMineNum;   //雷数LCD
    QPushButton *m_nowState;    //中间的按钮
    QGraphicsView *m_view;      //镜头
    myScence *m_scene;     //舞台
    QPixmap t_pixmap;   //游戏开始每个格子的图片
    OptionDialog *m_optionDialog;    //设置界面
    aboutdialog *m_aboutDialog;      //关于窗口
    finishDialog *m_finishDialog;   //踩雷后，游戏结束窗口
    statisticsDialog *m_statisticsDialog;    //统计窗口
    QTimer *m_timer;                //定时器，用来控制TimeLcd的变化
    int m_timeNum;                  //LcdTime的时间数
    int m_mineNum;                  //LcdMine的数字
    int m_rowNum;           //行
    int m_rankNum;          //列
    int m_nummine;          //窗口默认雷数
    statisticsDialog::Record m_gameLevel;        //游戏难度


private:
    //创建菜单
    void createMenu();
    //创建中心窗体
    void createWidget();
    void createConnect();
    //设置中间窗口的格子行列和中间雷的数量
    void setCentreWidgetContent(int t_w,int t_h,int t_mineNum);




public slots:
    //游戏结束的槽函数
    void diaposeGameOver();
    //让lcd变化的槽函数
    void timeupdate();
    //开始计时的槽函数
    void recTimerOpen();
    //新游戏的槽函数
    void newgame();
    //雷数变化的槽函数
    void recshiftLcdMineNumchange(bool t_result);
    //游戏成功的槽函数
    void recshiftgameSuccess();
    //接受option界面传来的信号
    void recGameInfo(int t_x,int t_y,int t_mineNum);




};

#endif // CARTOON_H
