// ViewModel.h
#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QVector>
#include "model.h"

class ViewModel : public QObject
{
    Q_OBJECT

public:
    explicit ViewModel(Model *model, QObject *parent = nullptr);

    QVector<QVector<int>> getBoardState() const;

    void initializeBoard();
    void swapTiles(int x1, int y1, int x2, int y2);

    void onBoardStateChanged();
    void onTilesSwapped();
    void onTilesEliminated(const QVector<TilePosition>& tiles);
    void onTilesDropped();
    void onBoardUpdated();

    signals:
            void boardStateChanged();
    void tilesSwapped();
    void tilesEliminated(const QVector<TilePosition>& tiles);
    void tilesDropped();
    void boardUpdated();

private:
    Model *m_model;
};

#endif // VIEWMODEL_H