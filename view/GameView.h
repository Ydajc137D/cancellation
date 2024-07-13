#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QLabel>
#include <QTimer>
#include "ItemsPanel.h"

// 游戏界面类
class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);

    // 开始新游戏
    void startNewGame();

signals:
    // 游戏结束信号，带上最终分数
    void gameFinished(int finalScore);

private slots:
    // 处理道具被使用的槽函数
    void handleItemUsed(ItemType type);

private:
    QGridLayout *gameBoardLayout;    // 游戏面板的布局
    QVector<QVector<QLabel*>> gameBoard; // 游戏方格
    ItemsPanel *itemsPanel;          // 道具面板指针
    int score;                       // 当前分数
    QTimer *animationTimer;          // 动画定时器

    // 初始化游戏界面
    void initGameView();

    // 初始化游戏板块
    void initGameBoard();

    // 处理元素点击事件
    void handleClick(int row, int col);

    // 消除相同元素逻辑
    void eliminateItems();

    // 更新游戏分数
    void updateScore(int points);


    // 结束游戏并触发游戏结束信号
    void checkGameOver();
};

#endif // GAMEVIEW_H
