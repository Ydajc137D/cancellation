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
    // 假设 viewmodel 提供了获取两个要交换的图元的方法
    QGraphicsItem *itemA = _viewModel->getSelectedTileA();
    QGraphicsItem *itemB = _viewModel->getSelectedTileB();

    // 检查是否两个图元都是有效的并且不相同
    if (!itemA || !itemB || itemA == itemB) {
        return; // 如果有任何一个图元无效或者相同，终止动画
    }

    // 创建交换动画
    QPropertyAnimation *animationAtoB = new QPropertyAnimation(itemA, "pos");
    animationAtoB->setDuration(200);
    animationAtoB->setStartValue(itemA->pos());
    animationAtoB->setEndValue(itemB->pos());
    animationAtoB->start();

    QPropertyAnimation *animationBtoA = new QPropertyAnimation(itemB, "pos");
    animationBtoA->setDuration(200);
    animationBtoA->setStartValue(itemB->pos());
    animationBtoA->setEndValue(itemA->pos());
    animationBtoA->start();

    // 将动画添加到动画列表中，以便于清理
    _animations.append(animationAtoB);
    _animations.append(animationBtoA);

    // 当第一个动画完成时开始第二个动画，形成来回的效果
    connect(animationAtoB, &QPropertyAnimation::finished, animationBtoA, &QPropertyAnimation::start);
    connect(animationBtoA, &QPropertyAnimation::finished, animationAtoB, &QPropertyAnimation::start);

    // 当动画完成两次交换后，清除动画并重置选择状态
    connect(animationAtoB, &QPropertyAnimation::finished, this, [this, animationAtoB]() {
        if (animationAtoB->direction() == QAbstractAnimation::Backward) {
            _viewModel->resetSelectedTiles(); // 假设此方法重置选择状态
            onAnimationFinished();
        }
    });
}

void GameView::showThreeInARowEliminationAnimation()
{
    // 假设_gameModel->getEliminatedTilesForThreeInARow() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getEliminatedTilesForThreeInARow();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 在消除动画完成后，更新该列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnAfterThreeInARowElimination();
    });
}

void GameView::showThreeInALineEliminationAnimation()
{
    // 假设_gameModel->getEliminatedTilesForThreeInALine() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getEliminatedTilesForThreeInALine();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 在消除动画完成后，更新受影响的列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnsAfterThreeInALineElimination();
    });
}

void GameView::showFourInARowEliminationAnimation()
{
    // 假设_gameModel->getEliminatedTilesForRowEliminationFour() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getEliminatedTilesForRowEliminationFour();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 假设 _viewModel->generateRowEliminatorAt() 会在交换位置生成行消除方块
    _viewModel->generateRowEliminatorAt(tiles.first()->pos());

    // 在消除动画完成后，更新所有受影响的列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnsAfterRowElimination();
    });
}

void GameView::showFourInAColumnEliminationAnimation()
{
    // 假设 _viewModel->getEliminatedTilesForColumnEliminationFour() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getEliminatedTilesForColumnEliminationFour();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 假设 _viewModel->generateColumnEliminatorAt() 会在交换位置生成列消除方块
    _viewModel->generateColumnEliminatorAt(tiles.first()->pos());

    // 在消除动画完成后，更新该列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnAfterColumnElimination();
    });
}

void GameView::showFiveInARowFormationAnimation()
{
    // 假设 _viewModel->getEliminatedTilesForRowEliminationFive() 返回需要消除的方块列表
    auto tiles = _viewModel->getEliminatedTilesForRowEliminationFive();

    // 创建消除动画组
    QSequentialAnimationGroup *fadeOutGroup = new QSequentialAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOutGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
    }

    // 假设 _viewModel->generateRainbowCircleAt() 会在交换位置生成彩虹圈方块
    _viewModel->generateRainbowCircleAt(tiles.first()->pos());

    // 连接消除动画组完成信号到列更新槽函数
    connect(fadeOutGroup, &QSequentialAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->updateColumnsAfterRainbowCircle() 更新所有受影响的列
        _viewModel->updateColumnsAfterRainbowCircle();
    });

    // 启动消除动画组
    fadeOutGroup->start();
}

void GameView::showFiveInALineFormationAnimation()
{
    // 假设 _viewModel->getEliminatedTilesForColumnEliminationFive() 返回需要消除的方块列表
    auto tiles = _viewModel->getEliminatedTilesForColumnEliminationFive();

    // 创建消除动画组
    QSequentialAnimationGroup *fadeOutGroup = new QSequentialAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOutGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
    }

    // 假设 _viewModel->generateRainbowCircleAt() 会在交换位置生成彩虹圈方块
    _viewModel->generateRainbowCircleAt(tiles.first()->pos());

    // 连接消除动画组完成信号到列更新槽函数
    connect(fadeOutGroup, &QSequentialAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->updateColumnAfterRainbowCircle() 更新该列
        _viewModel->updateColumnAfterRainbowCircle();
    });

    // 启动消除动画组
    fadeOutGroup->start();
}

void GameView::showLShapeFormationAnimation()
{
    // 假设 _viewModel->getEliminatedTilesForLShapeFormation() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getEliminatedTilesForLShapeFormation();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 假设 _viewModel->generateBombAt() 会在L形的拐角坐标处生成新功能方块“炸弹”
    _viewModel->generateBombAt(tiles.first()->pos());

    // 在消除动画完成后，更新所有受影响的列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnsAfterLShapeElimination();
    });
}

void GameView::showBombEffectAnimation()
{
    // 假设 _viewModel->getTilesAffectedByBombEffect() 返回被炸弹影响的方块列表
    QList<QGraphicsItem*> affectedTiles = _viewModel->getTilesAffectedByBombEffect();

    // 创建消除动画
    QSequentialAnimationGroup *bombEffectGroup = new QSequentialAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : affectedTiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        bombEffectGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 连接消除动画组完成信号到列更新槽函数
    connect(bombEffectGroup, &QSequentialAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->updateColumnsAfterBombEffect() 更新所有受影响的列
        _viewModel->updateColumnsAfterBombEffect();
    });

    // 启动消除动画组
    bombEffectGroup->start();
}

void GameView::showRowEliminatorEffectAnimation()
{
    // 假设 _viewModel->getTilesAffectedByRowEliminator() 返回被行消除者影响的方块列表
    QList<QGraphicsItem*> affectedTiles = _viewModel->getTilesAffectedByRowEliminator();

    // 创建消除动画
    QSequentialAnimationGroup *rowEliminationGroup = new QSequentialAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : affectedTiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        rowEliminationGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 连接消除动画组完成信号到列更新槽函数
    connect(rowEliminationGroup, &QSequentialAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->updateColumnsAfterRowElimination() 更新所有受影响的列
        _viewModel->updateColumnsAfterRowElimination();
    });

    // 启动消除动画组
    rowEliminationGroup->start();
}

void GameView::showColumnEliminatorEffectAnimation()
{
    // 假设 _viewModel->getTilesAffectedByColumnEliminator() 返回被列消除者影响的方块列表
    QList<QGraphicsItem*> affectedTiles = _viewModel->getTilesAffectedByColumnEliminator();

    // 创建消除动画
    QSequentialAnimationGroup *columnEliminationGroup = new QSequentialAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : affectedTiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        columnEliminationGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 连接消除动画组完成信号到列更新槽函数
    connect(columnEliminationGroup, &QSequentialAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->updateColumnAfterColumnElimination() 更新受影响的列
        _viewModel->updateColumnAfterColumnElimination();
    });

    // 启动消除动画组
    columnEliminationGroup->start();
}

void GameView::showRainbowCircleEffectAnimation()
{
    // 假设 _viewModel->getTilesToEliminateByRainbowCircle() 返回需要消除的方块列表
    QList<QGraphicsItem*> tiles = _viewModel->getTilesToEliminateByRainbowCircle();

    // 创建消除动画
    for (QGraphicsItem *tile : tiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->start();
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 在消除动画完成后，更新所有受影响的列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnsAfterRainbowCircleEffect();
    });
}

void GameView::showDeletionEffectAnimation()
{
    // 假设 _viewModel->getTileToDelete() 返回要消除的单个方块
    QGraphicsItem *tile = _viewModel->getTileToDelete();

    // 创建消除动画
    QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
    fadeOut->setDuration(300); // 动画时长
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start();
    _animations.append(fadeOut);
    connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);

    // 在消除动画完成后，更新受影响的列
    QTimer::singleShot(300, this, [this]() {
        _viewModel->updateColumnAfterDeletionEffect(tile->pos());
    });
}

void GameView::showMakeBombEffectAnimation()
{
    // 假设 _viewModel->getTargetTileForMakeBombEffect() 返回目标方块
    QGraphicsItem* targetTile = _viewModel->getTargetTileForMakeBombEffect();

    // 创建消失动画
    QPropertyAnimation* fadeOut = new QPropertyAnimation(targetTile, "opacity");
    fadeOut->setDuration(300); // 动画时长
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start();
    _animations.append(fadeOut);
    connect(fadeOut, &QPropertyAnimation::finished, this, [this, targetTile]() {
        // 在原方块消失后，生成炸弹方块
        _viewModel->placeBombAt(targetTile->pos());
        // 更新UI显示新的炸弹方块
        updateView();
    });
}

void GameView::showMakeRowEliminatorEffectAnimation()
{
    // 假设 _viewModel->getTargetTileForMakeRowEliminatorEffect() 返回目标方块
    QGraphicsItem* targetTile = _viewModel->getTargetTileForMakeRowEliminatorEffect();

    // 创建消失动画
    QPropertyAnimation* fadeOut = new QPropertyAnimation(targetTile, "opacity");
    fadeOut->setDuration(300); // 动画时长
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start();
    _animations.append(fadeOut);
    connect(fadeOut, &QPropertyAnimation::finished, this, [this, targetTile]() {
        // 在原方块消失后，生成行消除方块
        _viewModel->placeRowEliminatorAt(targetTile->pos());
        // 更新UI显示新的行消除方块
        updateView();
    });
}

void GameView::showMakeColumnEliminatorEffectAnimation()
{
    // 假设 _viewModel->getTargetTileForMakeColumnEliminatorEffect() 返回目标方块
    QGraphicsItem* targetTile = _viewModel->getTargetTileForMakeColumnEliminatorEffect();

    // 创建消失动画
    QPropertyAnimation* fadeOut = new QPropertyAnimation(targetTile, "opacity");
    fadeOut->setDuration(300); // 动画时长
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start();
    _animations.append(fadeOut);
    connect(fadeOut, &QPropertyAnimation::finished, this, [this, targetTile]() {
        // 在原方块消失后，生成列消除方块
        _viewModel->placeColumnEliminatorAt(targetTile->pos());
        // 更新UI显示新的列消除方块
        updateView();
    });
}

void GameView::showRefreshAllEffectAnimation()
{
    // 假设 _viewModel->getAllNormalTiles() 返回所有普通方块的列表
    QList<QGraphicsItem*> normalTiles = _viewModel->getAllNormalTiles();

    // 创建消除动画组
    QParallelAnimationGroup *fadeOutGroup = new QParallelAnimationGroup(this);

    // 创建消除动画
    for (QGraphicsItem *tile : normalTiles) {
        QPropertyAnimation* fadeOut = new QPropertyAnimation(tile, "opacity");
        fadeOut->setDuration(300); // 动画时长
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOutGroup->addAnimation(fadeOut);
        _animations.append(fadeOut);
        connect(fadeOut, &QPropertyAnimation::finished, this, &GameView::onAnimationFinished);
    }

    // 连接消除动画组完成信号到刷新棋盘的槽函数
    connect(fadeOutGroup, &QParallelAnimationGroup::finished, this, [this]() {
        // 假设 _viewModel->refreshAllNormalTiles() 负责刷新所有普通方块
        _viewModel->refreshAllNormalTiles();
    });

    // 启动消除动画组
    fadeOutGroup->start();
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

//void GameView::onTimerTimeout()
//{
    //定时器超时事件处理
//}

void GameView::onAnimationFinished()
{
    // 动画完成事件处理
    QPropertyAnimation *animation = qobject_cast<QPropertyAnimation*>(sender());
    if (animation && _animations.contains(animation)) {
        _animations.removeOne(animation);
        animation->deleteLater();
    }
}