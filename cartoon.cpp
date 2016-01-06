#include "cartoon.h"


cartoon::cartoon(QWidget *parent)
    : QMainWindow(parent),m_gameMenu(0),m_helpMenu(0),m_newGameAct1(0),m_statisticsInfoAct2(0),
      m_aboutAct(0),m_centreWidget(0),m_vLayout(0),m_view(0),m_scene(0),t_pixmap(QPixmap(":images/0.png")),
      m_optionAct3(0),m_exitAct4(0),m_optionDialog(new OptionDialog),m_hLayout(0),m_lcdTime(0),m_lcdMineNum(0),
      m_nowState(0),m_aboutDialog(new aboutdialog),m_finishDialog(new finishDialog),m_timer(new QTimer),m_timeNum(0),
      m_rowNum(9),m_rankNum(9),m_nummine(10),m_statisticsDialog(new statisticsDialog),m_gameLevel(statisticsDialog::PRIMARY)
{

    createMenu();
    createWidget();
    createConnect();


    this->setWindowTitle("扫雷");

//    this->setWindowIcon(QIcon(":/images/tubiao.ico"));






    //将最小化和关闭按钮设置为可操作
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

}

cartoon::~cartoon()
{

}


//创建菜单
void cartoon::createMenu()
{
    //增加菜单
    m_gameMenu = new QMenu("游戏",this);
    m_helpMenu = new QMenu("帮助",this);

    //增加子选项
    m_newGameAct1 = new QAction("新游戏",this);
    m_statisticsInfoAct2 = new QAction("统计信息",this);
    m_optionAct3 = new QAction("选项",this);
    m_exitAct4 = new QAction("退出",this);

    m_aboutAct = new QAction("关于",this);

    m_gameMenu->addAction(m_newGameAct1);
    m_gameMenu->addAction(m_statisticsInfoAct2);
    m_gameMenu->addAction(m_optionAct3);
    m_gameMenu->addAction(m_exitAct4);

    m_helpMenu->addAction(m_aboutAct);

    //设置快捷键
    m_newGameAct1->setShortcut(QKeySequence(Qt::Key_F2));
    m_statisticsInfoAct2->setShortcut(QKeySequence(Qt::Key_F3));

    m_optionAct3->setShortcut(QKeySequence(Qt::Key_F4));

    m_exitAct4->setShortcut(QKeySequence(Qt::Key_X));

    this->menuBar()->addMenu(m_gameMenu);
    this->menuBar()->addMenu(m_helpMenu);

}

//创建中心窗体
void cartoon::createWidget()
{

    //增加中心窗体
    m_centreWidget = new QWidget;
    //增加lcd和按键
    m_lcdTime = new QLCDNumber;
    m_lcdMineNum = new QLCDNumber;
    m_lcdTime->setFixedWidth(70);
    m_lcdMineNum->setFixedWidth(70);
    //中间的按钮
    m_nowState = new QPushButton(QIcon(":/images/smile.gif"),"",this);

    //设置按键的大小
    m_nowState->setFixedWidth(30);
    //增加两个垫片
    m_spacer1 = new QSpacerItem(50,0);
    m_spacer2 = new QSpacerItem(50,0);
    //增加水平布局
    m_hLayout = new QHBoxLayout;
    m_hLayout->addWidget(m_lcdTime);
    m_hLayout->addSpacerItem(m_spacer1);
    m_hLayout->addWidget(m_nowState);
    m_hLayout->addSpacerItem(m_spacer2);
    m_hLayout->addWidget(m_lcdMineNum);
    //增加垂直布局
    m_vLayout = new QVBoxLayout(m_centreWidget);
    //增加舞台
    m_scene = new myScence;
    //增加镜头
    m_view = new QGraphicsView(m_scene);
    //将镜头放到垂直布局中去
    m_vLayout->addLayout(m_hLayout);
    m_vLayout->addWidget(m_view);
    //设置中心框体设置到主窗体中
    this->setCentralWidget(m_centreWidget);

    setCentreWidgetContent(m_rowNum,m_rankNum,m_nummine);


}

void cartoon::createConnect()
{
    connect(m_exitAct4,SIGNAL(triggered()),this,SLOT(close()));     //将退出ACTION和关闭窗口关联
    connect(m_aboutAct,SIGNAL(triggered()),m_aboutDialog,SLOT(exec())); //关联按钮
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeupdate()));         //超时和LCD的连接

    connect(m_newGameAct1,SIGNAL(triggered()),this,SLOT(newgame()));
    connect(m_optionAct3,SIGNAL(triggered()),m_optionDialog,SLOT(exec()));
    connect(m_nowState,SIGNAL(clicked()),this,SLOT(newgame()));
    connect(m_finishDialog,SIGNAL(sndExitGAME()),this,SLOT(close()));
    connect(m_finishDialog,SIGNAL(sndGameAgain()),this,SLOT(newgame()));
    connect(m_newGameAct1,SIGNAL(triggered()),this,SLOT(newgame()));
    connect(m_optionDialog,SIGNAL(sndGameInfo(int,int,int)),this,SLOT(recGameInfo(int,int,int)));
    connect(m_statisticsInfoAct2,SIGNAL(triggered()),m_statisticsDialog,SLOT(exec()));


}

//设置中间窗口的格子行列和中间雷的数量
//其中t_w表示x轴的格子数 t_y 表示y轴的格子数
void cartoon::setCentreWidgetContent(int t_w, int t_h, int t_mineNum)
{
    //销毁舞台
    delete m_scene;
    m_scene = NULL;
    //重建舞台
    m_scene = new myScence;
    m_view->setScene(m_scene);
    connect(m_scene,SIGNAL(gameover()),this,SLOT(diaposeGameOver()));   //点到雷后
    connect(m_scene,SIGNAL(shiftTimerOpen()),this,SLOT(recTimerOpen()));//当点击，开始计数
    connect(m_scene,SIGNAL(shiftLcdMineNumchange(bool)),this,SLOT(recshiftLcdMineNumchange(bool)));
    connect(m_scene,SIGNAL(shiftgameSuccess()),this,SLOT(recshiftgameSuccess()));
    m_nowState->setIcon(QIcon(":/images/smile.gif"));
    m_statisticsDialog->openStatisticsFile();

    m_rowNum = t_w;
    m_rankNum = t_h;
    m_nummine = t_mineNum;
    //将雷数，行数，列数保存
    m_scene->m_rowNum = t_w;    //x轴的个数
    m_scene->m_rankNum = t_h;   //y轴的个数
    m_scene->m_mineNum = t_mineNum; //雷的数量
    m_scene->m_notMineNum =(t_w*t_h) - t_mineNum;//不是雷的数量
    m_mineNum = t_mineNum;
    m_lcdMineNum->display(t_mineNum);

    qreal t_ImgWidth = t_pixmap.width();
    qreal t_ImgHeight = t_pixmap.height();

    //增加道具
    for(int i = 0;i < t_w;i++)
    {
        vector<myItem *> tmp;
        for(int j = 0;j < t_h;j++)
        {
            myItem *t_myItem = new myItem(i,j,t_pixmap);
            t_myItem->setPos(i*t_ImgWidth,j*t_ImgHeight);
            tmp.push_back(t_myItem);
            m_scene->addItem(t_myItem);
        }
        m_scene->m_itemVec.push_back(tmp);
    }
    //设置场景的高度和宽度
    m_scene->setSceneRect(0,0,t_w*t_ImgWidth,t_h*t_ImgHeight);
    m_view->setFixedSize(m_scene->width()+5,m_scene->height()+5);
    this->setFixedWidth(m_scene->width()+22);
    this->setFixedHeight(m_scene->height()+72);

    srand(time(0));
    //随机雷的位置
    while(t_mineNum)
    {
        int t_x = rand()%t_w;
        int t_y = rand()%t_h;
        if(m_scene->m_itemVec[t_x][t_y]->m_mineNum != -1)
        {
            m_scene->m_itemVec[t_x][t_y]->m_mineNum = -1;

            t_mineNum--;
        }
    }

    //设置雷以外格子的数字
    for(int i = 0;i < t_w;i++)
    {
        for(int j = 0; j < t_h; j++)
        {
             if(m_scene->m_itemVec[i][j]->m_mineNum != -1)
             {  //如果要设置的格子不是雷，就看这个格子边上的格子有几个雷
                 int t_mineNum = 0;
                 for(int m = i-1;m < i+2; m++)
                 {
                     for(int n = j -1;n < j+2;n++)
                     {//遍历边上的8个格子中雷的数量
                         //越界和等于自己的情况跳过
                         if(m < 0 ||(m >t_w-1) || n < 0|| (n > t_h-1) || (m == i && n ==j))
                         {
                             continue;
                         }
                         else
                         {
                             if(m_scene->m_itemVec[m][n]->m_mineNum == -1)
                             {
                                 t_mineNum++;
                             }
                         }
                     }

                 }
                 m_scene->m_itemVec[i][j]->m_mineNum  = t_mineNum;
             }
        }
    }
    //为整个场景创建连接
    m_scene->createConnect();


}

void cartoon::diaposeGameOver()
{  //翻开所有的图片
    m_nowState->setIcon(QIcon(":/images/cry.gif"));
    m_scene->openAllPixmap();
    m_timer->stop();
    if(m_optionDialog->m_soundPlay == true)
    {
        QSound::play(":/sounds/fail.wav");
    }

    m_finishDialog->setGameOverTime(m_timeNum);
    m_finishDialog->exec();
}

void cartoon::timeupdate()
{
//    qDebug() << "timeupdate";
    m_lcdTime->display(++m_timeNum);
    if(m_optionDialog->m_soundPlay == true)
    {
        QSound::play(":/sounds/time.wav");
    }

}

void cartoon::recTimerOpen()
{
    m_timer->start(1000);
}

void cartoon::newgame()
{
    qDebug() << "new game!";

    m_timer->stop();
    m_timeNum=0;
    m_lcdTime->display(m_timeNum);
    setCentreWidgetContent(m_rowNum,m_rankNum, m_nummine);

}

void cartoon::recshiftLcdMineNumchange(bool t_result)
{
    qDebug() << "recshiftLcdMineNumchange";
    if(t_result == true)
    {
        m_lcdMineNum->display(--m_mineNum);
    }
    else
    {
        m_lcdMineNum->display(++m_mineNum);
    }

}

void cartoon::recshiftgameSuccess()
{
    //打开所有图片
     m_scene->openAllPixmap();
    //时间停止
     m_timer->stop();
    //把int型转换成字符串
     char buf[10];
     itoa(m_timeNum, buf, 10);
     QString t_timeStr = QString(buf);
    //雷数显示为0
     m_lcdMineNum->display(0);
     if(m_optionDialog->m_soundPlay == true)
     {  //如果声音打开的就播放胜利的声音
         QSound::play(":/sounds/win.wav");
     }
     QMessageBox::information(this,"恭喜","恭喜您赢得了这场比赛,你花的时间为："+t_timeStr+"秒",QMessageBox::Ok);

     switch(m_gameLevel)
     {//发送游戏时间
     case statisticsDialog::PRIMARY:
         m_statisticsDialog->refreshRecond(statisticsDialog::PRIMARY,m_timeNum);
         break;
     case statisticsDialog::MIDDLE:
         m_statisticsDialog->refreshRecond(statisticsDialog::MIDDLE,m_timeNum);
         break;
     case statisticsDialog::HIGH:
         m_statisticsDialog->refreshRecond(statisticsDialog::HIGH,m_timeNum);
         break;
     }

}

void cartoon::recGameInfo(int t_x, int t_y, int t_mineNum)
{

    qDebug() << t_x << t_y << t_mineNum;
    //修改游戏难度，如果和原来的难度不同，更改原来的难度
    if(t_x != m_rowNum || t_y != m_rankNum || t_mineNum !=m_nummine)
    {
        m_rowNum = t_x;
        m_rankNum = t_y;
        m_nummine = t_mineNum;

        if(m_rowNum == 9 && m_rankNum == 9 && m_nummine == 10)
        {
            m_gameLevel = statisticsDialog::PRIMARY;
        }
        else if(m_rowNum == 16 && m_rankNum == 16 && m_nummine == 40)
        {
            m_gameLevel = statisticsDialog::MIDDLE;
        }
        else if(m_rowNum == 30 && m_rankNum == 16 && m_nummine == 99)
        {
            m_gameLevel = statisticsDialog::HIGH;
        }
        newgame();
    }

}


