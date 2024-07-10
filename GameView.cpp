// GameView.cpp
#include "GameView.h"
#include "GameViewModel.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QRandomGenerator>

GameView::GameView(QWidget *parent)
        : QGraphicsView(parent),
          _viewModel(nullptr),
          _scene(new QGraphicsScene(this)),
          _animations()
{
    setScene(_scene);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setCacheMode(QGraphicsView::CacheBackground);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

GameView::~GameView()
{
    qDeleteAll(_animations);
    delete _scene;
}

void GameView::setViewModel(GameViewModel *viewModel)
{
    _viewModel = viewModel;
    connect(_viewModel, &GameViewModel::gameStateChanged, this, &GameView::updateView);
}

void GameView::showSwapInvalidAnimation()
{
    // 创建动画，这里假设我们有交换前后的两个图元
    QGraphicsItem *itemA = _scene->items().first();
    QGraphicsItem *itemB = _scene->items().last();

    QPropertyAnimation *animationA = new QPropertyAnimation(itemA, "pos");
    animationA->setDuration(500);
    animationA->setStartValue(itemB->pos());
    animationA->setEndValue(itemA->pos());
    animationA->start();

    QPropertyAnimation *animationB = new QPropertyAnimation(itemB, "pos");
    animationB->setDuration(500);
    animationB->setStartValue(itemA->pos());
    animationB->setEndValue(itemB->pos());
    animationB->start();

    _animations.append(animationA);
    _animations.append(animationB);
    connect(animationA, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    connect(animationB, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
}

void GameView::showThreeInARowEliminationAnimation()
{
    // 假设_gameModel->getEliminatedTiles() 返回一个QList<QGraphicsItem*>，其中包含所有要消除的方块
    QList<QGraphicsItem*> tilesToEliminate = _viewModel->getEliminatedTiles();

    // 遍历要消除的方块，创建动画使其逐渐消失
    for (QGraphicsItem *tile : tilesToEliminate) {
        QPropertyAnimation *fadeAnimation = new QPropertyAnimation(tile, "opacity");
        fadeAnimation->setDuration(500);
        fadeAnimation->setStartValue(1.0);
        fadeAnimation->setEndValue(0.0);
        fadeAnimation->start();
        _animations.append(fadeAnimation);
        connect(fadeAnimation, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 假设_gameModel->getTilesToFall() 返回一个QMap<int, QList<QGraphicsItem*>>，其中key是列号，value是一列中要下落的方块
    QMap<int, QList<QGraphicsItem*>> tilesToFalling = _viewModel->getTilesToFall();

    // 遍历每一列，为每个方块创建下落动画
    for (auto it = tilesToFalling.begin(); it != tilesToFalling.end(); ++it) {
        for (QGraphicsItem *tile : it.value()) {
            QPropertyAnimation *fallAnimation = new QPropertyAnimation(tile, "pos");
            fallAnimation->setDuration(500);
            fallAnimation->setStartValue(tile->pos());
            fallAnimation->setEndValue(tile->pos() + QPointF(0, it.key() * tile->boundingRect().height()));
            fallAnimation->start();
            _animations.append(fallAnimation);
            connect(fallAnimation, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
        }
    }
}

void GameView::showThreeInALineEliminationAnimation()
{
    // 与showThreeInARowEliminationAnimation类似，但是这里需要遍历行而不是列
    QList<QGraphicsItem*> tilesToEliminate = _viewModel->getEliminatedTiles();

    // 消除方块的动画
    for (QGraphicsItem *tile : tilesToEliminate) {
        QPropertyAnimation *fadeAnimation = new QPropertyAnimation(tile, "opacity");
        fadeAnimation->setDuration(500);
        fadeAnimation->setStartValue(1.0);
        fadeAnimation->setEndValue(0.0);
        fadeAnimation->start();
        _animations.append(fadeAnimation);
        connect(fadeAnimation, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 获取要下落的方块
    QMap<int, QList<QGraphicsItem*>> tilesToFalling = _viewModel->getTilesToFall();

    // 下落动画，但这次是基于行
    for (auto it = tilesToFalling.begin(); it != tilesToFalling.end(); ++it) {
        for (QGraphicsItem *tile : it.value()) {
            QPropertyAnimation *fallAnimation = new QPropertyAnimation(tile, "pos");
            fallAnimation->setDuration(500);
            fallAnimation->setStartValue(tile->pos());
            fallAnimation->setEndValue(tile->pos() + QPointF(it.key() * tile->boundingRect().width(), 0));
            fallAnimation->start();
            _animations.append(fallAnimation);
            connect(fallAnimation, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
        }
    }
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    // 鼠标按下事件处理
    QGraphicsView::mousePressEvent(event);
}

void GameView::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标释放事件处理
    QGraphicsView::mouseReleaseEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动事件处理
    QGraphicsView::mouseMoveEvent(event);
}

void GameView::onTimerTimeout()
{
    // 定时器超时事件处理
}

void GameView::onAnimationFinished()
{
    // 动画完成事件处理
    QPropertyAnimation *animation = qobject_cast<QPropertyAnimation*>(sender());
    if (animation && _animations.contains(animation)) {
        _animations.removeOne(animation);
        animation->deleteLater();
    }
}