#ifndef DIFFICULTYSELECTOR_H
#define DIFFICULTYSELECTOR_H

#include <QObject>

class DifficultySelector : public QObject
{
    Q_OBJECT

public:
    explicit DifficultySelector(QObject *parent = nullptr);

public slots:
    void selectEasy();
    void selectHard();

signals:
    void difficultySelected(QString difficulty);
};

#endif // DIFFICULTYSELECTOR_H