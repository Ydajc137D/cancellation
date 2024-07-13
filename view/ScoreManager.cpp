#include "ScoreManager.h"

ScoreManager::ScoreManager(QObject *parent) : QObject(parent)
{
}

void ScoreManager::addScore(int score, QString difficulty)
{
    ScoreEntry entry;
    entry.score = score;

    if (!scoresMap.contains(difficulty)) {
        scoresMap.insert(difficulty, QList<ScoreEntry>());
    }

    scoresMap[difficulty].append(entry);
}

QList<ScoreEntry> ScoreManager::getScores(QString difficulty) const
{
    if (scoresMap.contains(difficulty)) {
        return scoresMap.value(difficulty);
    } else {
        return QList<ScoreEntry>(); // 如果没有该难度的得分记录，则返回空列表
        //或者加入信息“未体验该难度”？
    }
}
