#include "myscence.h"
myScence::myScence(QObject *parent) :
    QGraphicsScene(parent),m_mineNum(0),m_rowNum(0),m_rankNum(0),m_notMineNum(0),m_timeOk(false)
{

}



void myScence::createConnect()
{
    for(int i = 0;i<m_rowNum;i++)
    {
        for(int j =0;j<m_rankNum;j++)
        {
            connect(m_itemVec[i][j],SIGNAL(sndEmptyState(int,int)),this,SLOT(recEmptyState(int,int)));
            connect(m_itemVec[i][j],SIGNAL(sndGameOver()),this,SLOT(recGameOver()));
            connect(m_itemVec[i][j],SIGNAL(sndTimerOpen()),this,SLOT(sendTimerOpen()));
            connect(m_itemVec[i][j],SIGNAL(sndLcdMineNUMchange(bool)),this,SLOT(recLcdMineNUMchange(bool)));
            connect(m_itemVec[i][j],SIGNAL(sndDoubleClickNumber(int,int)),this,SLOT(recDoubleClickNumber(int,int)));
            connect(m_itemVec[i][j],SIGNAL(gameSuccess()),this,SIGNAL(shiftgameSuccess()));


        }
    }
}

void myScence::openAllPixmap()
{
    for(int i = 0 ; i< m_rowNum;i++)
    {
        for(int j=0;j<m_rankNum;j++)
        {
            if( m_itemVec[i][j]->m_imgChange == 0)
            {       //没有翻开的，全部翻开
                 m_itemVec[i][j]->setmineNumPixmap();
            }

        }
    }
}


//水波函数
void myScence::recEmptyState(int t_x, int t_y)
{
//    qDebug() << "recEmptyState";
    //当点击到空白的时候，边上连着的出现

    for(int i = t_x-1;i<t_x+2;i++)
    {

        for(int j = t_y-1;j < t_y+2;j++)
        {
            if(j < 0 || j >m_rankNum -1 || i < 0 || i > m_rowNum-1)
            {   //越出边界
                continue;
            }
            else
            {
                //没有翻开并且是没插旗的
                if(m_itemVec[i][j]->m_imgChange == 0 && m_itemVec[i][j]->m_flagState == false)
                {
                    if(m_itemVec[i][j]->m_mineNum == 0)
                    {
                        m_itemVec[i][j]->setmineNumPixmap();
                        m_itemVec[i][j]->m_imgChange = 1;
                        recEmptyState(i,j);
                    }
                    else if(m_itemVec[i][j]->m_mineNum != 0 && m_itemVec[i][j]->m_mineNum != -1)
                    {
                        m_itemVec[i][j]->setmineNumPixmap();
                        m_itemVec[i][j]->m_imgChange = 1;
                    }
                }
            }
        }

    }

}

void myScence::recGameOver()
{
    qDebug() << "你踩到雷了";
    emit gameover();
}

void myScence::sendTimerOpen()
{
//    qDebug() << "sendTimerOpen";
    emit shiftTimerOpen();
}

void myScence::recLcdMineNUMchange(bool t_result)
{
    emit shiftLcdMineNumchange(t_result);
}


//双击点击数字的槽函数
void myScence::recDoubleClickNumber(int t_x, int t_y)
{
    qDebug() << "111111111";
    bool t_result =false;

    for(int i = t_x-1;i<t_x+2;i++)
    {   //附近的八个位置

        for(int j = t_y-1;j < t_y+2;j++)
        {   //双击的时候将边上没有翻开的，并且没有插旗子的翻开

            if(j < 0 || j >m_rankNum -1 || i < 0 || i > m_rowNum-1)
            {
                continue;
            }
            else
            {
                if(m_itemVec[i][j]->m_imgChange == 0 && m_itemVec[i][j]->m_flagState == false)
                {
                    if(m_itemVec[i][j]->m_mineNum == 0)
                    {
                       recEmptyState(i,j);
                    }
                    else
                    {
                        m_itemVec[i][j]->setmineNumPixmap();
                        if(m_itemVec[i][j]->m_mineNum == -1)
                        {   //其中有雷的情况
                            qDebug() << "recDoubleClickNumber";
//                            emit gameover();
                            t_result=true;

                        }
                    }


                }
            }

        }
    }


    if(t_result)
    {
        emit gameover();
    }

}


