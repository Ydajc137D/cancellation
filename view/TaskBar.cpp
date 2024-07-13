#include "taskbar.h"

TaskBar::TaskBar(QObject *parent)
    : QObject(parent)
{
    // 初始化
}

void TaskBar::addTask(const QString &title, const QString &description)
{
    Task newTask;
    newTask.title = title;
    newTask.description = description;
    newTask.completed = false;

    tasks.append(newTask);

    emit taskAdded(newTask);
}

bool TaskBar::markTaskAsCompleted(int index)
{
    if (index < 0 || index >= tasks.size()) {
        return false; // 索引无效，返回失败
    }

    tasks[index].completed = true;

    emit taskCompleted(index);

    return true;
}

QVector<Task> TaskBar::getAllTasks() const
{
    return tasks;
}
