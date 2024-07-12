// ViewModel.cpp
#include "QMetaType"
#include "viewmodel.h"
#include "model.h"

Q_DECLARE_METATYPE(TilePosition)
Q_DECLARE_METATYPE(QVector<TilePosition>)

ViewModel::ViewModel(Model *model, QObject *parent)
        : QObject(parent), m_model(model)
{
    connect(m_model, &Model::boardStateChanged, this, &ViewModel::onBoardStateChanged);
    connect(m_model, &Model::tilesSwapped, this, &ViewModel::onTilesSwapped);
    connect(m_model, &Model::tilesEliminated, this, &ViewModel::onTilesEliminated);
    connect(m_model, &Model::tilesDropped, this, &ViewModel::onTilesDropped);
    connect(m_model, &Model::boardUpdated, this, &ViewModel::onBoardUpdated);
}

QVector<QVector<int>> ViewModel::getBoardState() const
{
    return m_model->getBoardState();
}

void ViewModel::initializeBoard()
{
    m_model->initializeBoard();
}

void ViewModel::swapTiles(int x1, int y1, int x2, int y2)
{
    m_model->swapTiles(x1, y1, x2, y2);
}

void ViewModel::onBoardStateChanged()
{
    emit boardStateChanged();
}

void ViewModel::onTilesSwapped()
{
    emit tilesSwapped();
}

void ViewModel::onTilesEliminated(const QVector<TilePosition>& tiles)
{
    emit tilesEliminated(tiles);
}

void ViewModel::onTilesDropped()
{
    emit tilesDropped();
}

void ViewModel::onBoardUpdated()
{
    emit boardUpdated();
}