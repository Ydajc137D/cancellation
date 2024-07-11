#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView> // 确保包含QGraphicsView
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QPair>
#include <QVector>
#include <QGraphicsItem>

class AppController; // 前向声明AppController

class GameView : public QGraphicsView // 修改继承自QWidget为QGraphicsView
{
Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView() override;

    void setAppController(AppController *controller); // 设置AppController的引用

signals:
    void requestUpdateBoard(); // 请求更新棋盘的信号

public slots:
    void updateBoard(const QVector<QVector<int>>& boardState); // 更新棋盘状态的槽
    void startRowEliminationAnimation(const QList<QPair<int, int>>& positions); // 开始行消除动画
    void startColumnEliminationAnimation(const QList<QPair<int, int>>& positions); // 开始列消除动画

protected:
    void resizeEvent(QResizeEvent *event) override; // 覆写resizeEvent以处理视图的大小改变

private:
    QGraphicsScene *m_scene; // 用于渲染棋盘的场景
    AppController *m_controller; // 控制器引用
    QTimer m_animationTimer; // 动画计时器

    void createBoard(int sizeX, int sizeY); // 创建棋盘
    void updateBlock(int x, int y, int color); // 更新单个方块的颜色
    void startFadeOutAnimation(QList<QGraphicsItem*> items); // 开始淡出动画
};
#endif // GAMEVIEW_H