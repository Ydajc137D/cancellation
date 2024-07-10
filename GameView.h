// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPropertyAnimation>
#include <QList>

class GameViewModel;

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

    void setViewModel(GameViewModel *viewModel);

    void showSwapInvalidAnimation();
    void showThreeInARowEliminationAnimation();
    void showThreeInALineEliminationAnimation();
    //void showFourInARowEliminationAnimation();
    //void showFourInALineEliminationAnimation();
    //void showFiveInARowFormationAnimation();
    //void showFiveInALineFormationAnimation();
    //void showLShapeFormationAnimation();
    void showBombEffectAnimation();
    void showRowEliminatorEffectAnimation();
    void showColumnEliminatorEffectAnimation();
    void showColorChangerEffectAnimation();
    void showRainbowCircleEffectAnimation();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
            void onTimerTimeout();
    void onAnimationFinished();

private:
    GameViewModel *_viewModel;
    QGraphicsScene *_scene;
    QList<QPropertyAnimation*> _animations;
};
#endif // GAMEVIEW_H