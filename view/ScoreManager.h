#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QObject>
#include <QList>

struct ScoreEntry {
    int score;
    // 可以根据需要添加其他信息
};

class ScoreManager : public QObject
{
    Q_OBJECT

public:
    explicit ScoreManager(QObject *parent = nullptr);

    void addScore(int score, QString difficulty);
    QList<ScoreEntry> getScores(QString difficulty) const;

private:
    QMap<QString, QList<ScoreEntry>> scoresMap; // 用于存储不同难度级别的排行榜数据
};

#endif // SCOREMANAGER_H
