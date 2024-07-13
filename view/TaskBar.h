#ifndef TASKBAR_H
#define TASKBAR_H

#include <QObject>
#include <QVector>
#include <QString>

struct Task {
    QString title;
    QString description;//任务描述，收集水果或者收集分数？
    bool completed;
};


class TaskBar : public QObject
{
    Q_OBJECT

public:
    explicit TaskBar(QObject *parent = nullptr);

    void addTask(const QString &title, const QString &description);
    bool markTaskAsCompleted(int index);
    QVector<Task> getAllTasks() const;

signals:
    void taskAdded(const Task &task);
    void taskCompleted(int index);

private:
    QVector<Task> tasks;
};

#endif // TASKBAR_H
