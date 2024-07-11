#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QPair>
#include <QVector>
#include <QGraphicsItem>

class GameViewModel; // 前向声明GameViewModel

class GameView : public QGraphicsView
{
Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView() override;

    void setGameViewModel(GameViewModel *viewModel); // 设置GameViewModel的引用

signals:
    void requestUpdateBoard(); // 请求更新棋盘的信号

public slots:
    void updateBoard(const QVector<QVector<int>>& boardState); // 更新棋盘状态的槽
    void startRowEliminationAnimation(const QList<QPair<int, int>>& positions); // 开始行消除动画
    void startColumnEliminationAnimation(const QList<QPair<int, int>>& positions); // 开始列消除动画

private:
    QGraphicsScene *m_scene;
    GameViewModel *m_gameViewModel;
    QTimer m_animationTimer;

    void createBoard(int sizeX, int sizeY);
    void updateBlock(int x, int y, int color);
    void startFadeOutAnimation(QList<QGraphicsItem*> items);
};
#endif // GAMEVIEW_H