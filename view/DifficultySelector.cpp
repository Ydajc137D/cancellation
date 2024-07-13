#include "DifficultySelector.h"
#include <QDebug>

DifficultySelector::DifficultySelector(QObject *parent) : QObject(parent)
{

}

void DifficultySelector::selectEasy()
{
    emit difficultySelected("简单");
}

void DifficultySelector::selectHard()
{
    emit difficultySelected("困难");
}
