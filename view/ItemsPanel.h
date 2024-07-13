#ifndef ITEMSPANEL_H
#define ITEMSPANEL_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QIcon>

// 定义道具类型枚举
enum class ItemType {
    Hammer,
    Bomb
};//还有其他的

// 道具类的结构体定义
struct Item {
    ItemType type;        // 道具类型
    QString name;         // 道具名称
    QIcon icon;           // 道具图标
    int quantity;         // 道具剩余数量
};

class ItemsPanel : public QObject
{
    Q_OBJECT

public:
    explicit ItemsPanel(QObject *parent = nullptr);

    // 获取所有道具
    QVector<Item> getAllItems() const;

    // 使用道具
    bool useItem(ItemType type);

signals:
    // 信号：道具被使用
    void itemUsed(ItemType type);

private:
    QVector<Item> items;   // 存储所有道具的容器
};

#endif // ITEMSPANEL_H
