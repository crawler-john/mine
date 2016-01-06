#include "myitem.h"
#include "myscence.h"

myItem::myItem(int t_x, int t_y, const QPixmap &pixmap, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap,parent),m_X(t_x),m_Y(t_y),m_mineNum(0),m_imgChange(0),
      m_rightClickNum(0),m_flagState(0),m_questionState(false)
{

}



void myItem::setmineNumPixmap()
{
    myScence *t_scence = (myScence *)this->scene();
    m_imgChange = 1;
    t_scence->m_notMineNum--;
    switch(m_mineNum)
    {

    case -1:
    {
        this->setPixmap(QPixmap(":/images/lei.png"));

    }
        break;
    case 0:
    {
        this->setPixmap(QPixmap(":/images/empty.png"));

    }
        break;

    case 1:
    {
        this->setPixmap(QPixmap(":/images/1.png"));

    }
        break;
    case 2:
    {
        this->setPixmap(QPixmap(":/images/2.png"));
    }
        break;
    case 3:
    {
        this->setPixmap(QPixmap(":/images/3.png"));
    }
        break;
    case 4:
    {
        this->setPixmap(QPixmap(":/images/4.png"));
    }
        break;
    case 5:
    {
        this->setPixmap(QPixmap(":/images/5.png"));
    }
        break;
    case 6:
    {
        this->setPixmap(QPixmap(":/images/6.png"));
    }
        break;
    case 7:
    {
        this->setPixmap(QPixmap(":/images/7.png"));
    }
        break;
    case 8:
    {
        this->setPixmap(QPixmap(":/images/8.png"));
    }
        break;
    }


}



void myItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug() << "mousePressEvent";
    if(event->button() == Qt::RightButton)
    {
        m_rightClickNum++;
        qDebug() << "m_rightClickNum" << m_rightClickNum;
        int t_rightClickNum = m_rightClickNum%3;

        if(m_imgChange == 0)
        {
            switch(t_rightClickNum)
            {

            case 0:
            {
                this->setPixmap(QPixmap(":/images/0.png"));
                m_questionState = !m_questionState;
                m_flagState = !m_flagState;
                m_imgChange = 0;


            }
                break;
            case 1:
            {
                this->setPixmap(QPixmap(":/images/Flag.png"));
                m_flagState = !m_flagState;
                emit sndLcdMineNUMchange(true);

            }
                break;
            case 2:
            {
                this->setPixmap(QPixmap(":/images/question.png"));
                m_questionState = !m_questionState;
                emit sndLcdMineNUMchange(false);
            }
                break;
            }
        }
        m_rightClickNum = m_rightClickNum%3;
        qDebug() << m_rightClickNum;

    }
    if(event->button() == Qt::LeftButton)
    {
        if(m_imgChange == 0 && m_flagState != true &&m_questionState != true)
        {
            this->setPixmap(QPixmap(":/images/pit.png"));
        }
    }
}
void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug() << "mouseReleaseEvent";
    qDebug() << "X : " << m_X << " Y : " << m_Y;
    myScence *t_scence = (myScence *)this->scene();

    qDebug() << t_scence->m_notMineNum;
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "LeftButton";
        //左键释放动作
        if(m_flagState == false&&m_imgChange==0)
        {
            if(t_scence->m_timeOk == false)
            {
                emit sndTimerOpen();
                t_scence->m_timeOk = true;
            }
            m_imgChange = 1;
            t_scence->m_notMineNum--;
            switch(m_mineNum)
            {
            case -1:
            {
                this->setPixmap(QPixmap(":/images/lei.png"));                
                t_scence->m_notMineNum++;
                emit sndGameOver();
            }
                break;

            case 0:
            {
                this->setPixmap(QPixmap(":/images/empty.png"));
                //当点到空的时候，边上连续是空的都自动打开

                //告诉场景类，让它把边上连着的白块直接翻开
                emit sndEmptyState(m_X,m_Y);
            }
            break;
            case 1:
            {
                this->setPixmap(QPixmap(":/images/1.png"));
                qDebug() << t_scence->m_notMineNum;
            }
                break;
            case 2:
            {
                this->setPixmap(QPixmap(":/images/2.png"));
            }
                break;
            case 3:
            {
                this->setPixmap(QPixmap(":/images/3.png"));

            }
                break;
            case 4:
            {
                this->setPixmap(QPixmap(":/images/4.png"));
            }
                break;
            case 5:
            {
                this->setPixmap(QPixmap(":/images/5.png"));
            }
                break;
            case 6:
            {
                this->setPixmap(QPixmap(":/images/6.png"));
            }
                break;
            case 7:
            {
                this->setPixmap(QPixmap(":/images/7.png"));
            }
                break;
            case 8:
            {
                this->setPixmap(QPixmap(":/images/8.png"));
            }
                break;

            }
            if(t_scence->m_notMineNum == 0)
            {
                emit gameSuccess();
            }

        }

    }



}
void myItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug() << "mouseDoubleClickEvent";

    myScence* t_sence =(myScence*)this->scene();
    if(event->button() == Qt::LeftButton)
    {
        if(m_imgChange == 1&&m_mineNum != 0 && m_mineNum != -1)
        {
            qDebug() << m_mineNum;
            //双击的必须是翻开的数字,且不是雷和空白
            int t_flagNum = 0;
            //点击到后翻开边上的8个位置,如果边上的位置插的旗子数等于我的附近雷数
            for(int i = m_X-1;i<m_X+2;i++)
            {   //附近的八个位置

                for(int j = m_Y-1;j < m_Y+2;j++)
                {

                    if(j < 0 || j >t_sence->m_rankNum -1 || i < 0 || i >t_sence->m_rowNum-1)
                    {
                        continue;
                    }
                    else
                    {
                        if(t_sence->m_itemVec[i][j]->m_flagState == true)
                        {
                            t_flagNum++;
                        }
                    }

                }
            }

            if(t_flagNum == m_mineNum)
            {
                //发送一个信号翻开边上的八个位置
                emit sndDoubleClickNumber(m_X,m_Y);
            }
            if(t_sence->m_notMineNum == 0)
            {
                emit gameSuccess();
            }
        }

    }
}


