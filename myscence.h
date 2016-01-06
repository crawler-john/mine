#ifndef MYSCENCE_H
#define MYSCENCE_H

#include <QGraphicsScene>
#include <vector>
#include "myitem.h"

using namespace std;
class myScence : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScence(QObject *parent = 0);

    //建立一个容器来存放二维数组
    vector< vector<myItem*> > m_itemVec;

    //保存场景中的雷数，行，列
    int m_mineNum;  //雷数
    int m_notMineNum; //不是雷的数量
    int m_rowNum;   //在X轴上类的个数
    int m_rankNum;  //在y轴上类的个数
    //创建场景和item之间的连接
    void createConnect();
    //翻开所有的图片
    void openAllPixmap();
    bool m_timeOk;          //计时器是否打开



signals:
    void gameover();
    void shiftTimerOpen();
    void shiftLcdMineNumchange(bool t_result);
    void shiftgameSuccess();

public slots:
    void recEmptyState(int t_x,int t_y);
    void recGameOver();
    void sendTimerOpen();
    void recLcdMineNUMchange(bool t_result);

    //双击翻开的数字的槽函数
    void recDoubleClickNumber(int t_x,int t_y);


};

#endif // MYSCENCE_H
