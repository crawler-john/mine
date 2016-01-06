#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPixmapItem>
#include "QGraphicsSceneMouseEvent"
#include <QThread>
#include <QDebug>

class myItem :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT




public:
    myItem(int t_x,int t_y,const QPixmap & pixmap, QGraphicsItem * parent = 0);


    //设置成对应附近雷数的图片
    void setmineNumPixmap();


    //鼠标点击事件
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

    int m_mineNum; //-1为雷，0~8（表示附近类的数量）;

    int m_imgChange;    //当前的位置是否被翻开.如果被翻开了就是1，没有翻开就是0
    bool m_flagState;       //是否插旗
    bool m_questionState;   //是否问号
    int m_X;    //行数
    int m_Y;    //列数

private:


    int m_rightClickNum;    //右键点击的次数，点击的余数是1是插旗 2是问号  3是不变


signals:
    //自定义信号，用来发送自己的位置，如果是空的时候就发送信号
    void sndEmptyState(int t_x,int t_y);
    //踩到雷后，游戏结束
    void sndGameOver();
    //点击后发送时钟打开信号
    void sndTimerOpen();
    //插旗的时候，让lcdMineNum-1,问号的时候+1 // 真的话加一，假的话减一
    void sndLcdMineNUMchange(bool t_result);
    //双击数字的槽函数
    void sndDoubleClickNumber(int t_x,int t_y);
    //成功完成游戏的槽函数
    void gameSuccess();


public slots:
    

};

#endif // MYITEM_H
