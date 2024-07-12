// model.h
#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QVector>
#include <QHash>
#include <QString>

enum Difficulty { EASY, HARD };

/*enum ElementType {
    EMPTY,0
    APPLE,1
    ORANGE,2
    BANANA,3
    PEACH,4
    MANGO,5
    GRAPE,6
    ROW_CLEAR,-1
    COLUMN_CLEAR,-2
    BOMB,-3
    RAINBOW_CIRCLE£¬-4
};*/

enum ToolType { HAMMER, BOMB_TRANSFORM, REFRESH, ROW_CLEAR_TRANSFORM, COLUMN_CLEAR_TRANSFORM };


struct TilePosition {
    int row;
    int col;
};

class Model : public QObject
{
Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);
    ~Model();

    void initializeBoard();
    QVector<QVector<int>> getBoardState() const;

    void swapTiles(int x1, int y1, int x2, int y2);
    bool checkForMatches();
    void checkForMatches(QVector<TilePosition>& matches);
    void eliminateTiles(const QVector<TilePosition>& tiles);
    void applyGravity();
    void fillGaps();
    void updateBoardState();

signals:
    void boardStateChanged();
    void tilesSwapped();
    void tilesEliminated(const QVector<TilePosition>& tiles);
    void tilesDropped();
    void boardUpdated();

private:
    QVector<QVector<int>> m_board;
    void generateRandomColor(int& x, int& y);
};

#endif // MODEL_H