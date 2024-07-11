#include "GameView.h"
#include <QGraphicsRectItem>
#include <QColor>
#include <QTimer>
#include <QPropertyAnimation> // 添加这一行以包含QPropertyAnimation
#include <QDebug>

// 构造函数
GameView::GameView(QWidget *parent)
        : QGraphicsView(parent), m_controller(nullptr), m_scene(new QGraphicsScene(this))
{
    // 设置场景的大小
    m_scene->setSceneRect(0, 0, 1000, 1000);

    // 将场景添加到视图中
    setFixedSize(1000, 1000);
    setScene(m_scene); // 更改为QGraphicsView的成员函数
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 更改为QGraphicsView的成员函数
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 更改为QGraphicsView的成员函数

    // 创建棋盘
    createBoard(10, 10);

    // 连接动画计时器
    connect(&m_animationTimer, &QTimer::timeout, this, [this]() {
        m_animationTimer.stop();
        emit requestUpdateBoard();
    });
}

// 析构函数
GameView::~GameView()
{
    delete m_scene;
}

// 设置AppController的引用
void GameView::setAppController(AppController *controller)
{
    m_controller = controller;
}

// 创建棋盘
void GameView::createBoard(int sizeX, int sizeY)
{
    int blockSize = 100; // 每个方块的大小
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            QGraphicsRectItem *block = new QGraphicsRectItem(x * blockSize, y * blockSize, blockSize, blockSize);
            block->setBrush(Qt::white); // 默认颜色
            m_scene->addItem(block);
        }
    }
}

// 更新单个方块的颜色
void GameView::updateBlock(int x, int y, int color)
{
    auto block = qgraphicsitem_cast<QGraphicsRectItem*>(m_scene->itemAt(x * 100, y * 100, QTransform()));
    if (block) {
        switch (color) {
            case 0: block->setBrush(Qt::red); break;
            case 1: block->setBrush(Qt::yellow); break;
            case 2: block->setBrush(Qt::blue); break;
            case 3: block->setBrush(Qt::green); break;
            case 4: block->setBrush(Qt::magenta); break;
            case 5: block->setBrush(Qt::white); break;
            default: block->setBrush(Qt::white); break;
        }
    }
}

// 开始行消除动画
void GameView::startRowEliminationAnimation(const QList<QPair<int, int>>& positions)
{
    QList<QGraphicsItem*> itemsToFade;
    for (const auto &pos : positions) {
        itemsToFade.append(m_scene->itemAt(pos.first * 100, pos.second * 100, QTransform()));
    }

    startFadeOutAnimation(itemsToFade);
}

// 开始列消除动画
void GameView::startColumnEliminationAnimation(const QList<QPair<int, int>>& positions)
{
    QList<QGraphicsItem*> itemsToFade;
    for (const auto &pos : positions) {
        itemsToFade.append(m_scene->itemAt(pos.first * 100, pos.second * 100, QTransform()));
    }

    startFadeOutAnimation(itemsToFade);
}

// 开始淡出动画
void GameView::startFadeOutAnimation(QList<QGraphicsItem*> items)
{
    for (auto item : items) {
        if (item) {
            item->setOpacity(1.0); // 重置透明度
            QPropertyAnimation *animation = new QPropertyAnimation(reinterpret_cast<QObject *>(item), "opacity", this);
            animation->setDuration(1000); // 动画持续时间
            animation->setStartValue(1.0);
            animation->setEndValue(0.0);
            animation->start();
            connect(animation, &QPropertyAnimation::finished, this, [this]() {
                if (!m_animationTimer.isActive())
                    m_animationTimer.start(1000); // 等待一秒后请求更新棋盘
            });
        }
    }
}

// 更新棋盘状态
void GameView::updateBoard(const QVector<QVector<int>>& boardState)
{
    for (int y = 0; y < boardState.size(); ++y) {
        for (int x = 0; x < boardState[y].size(); ++x) {
            updateBlock(x, y, boardState[y][x]);
        }
    }
}