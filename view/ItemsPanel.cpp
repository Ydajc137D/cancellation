#include "itemspanel.h"

ItemsPanel::ItemsPanel(QObject *parent)
    : QObject(parent)
{
    // 初始化道具列表
    items.append(Item{ ItemType::Hammer, "锤子", QIcon(":/icon/hammer.png"), 0 });
    items.append(Item{ ItemType::Bomb, "炸弹", QIcon(":/icon/bomb.png"), 0 });
    // 可以在这里继续添加
}

QVector<Item> ItemsPanel::getAllItems() const
{
    return items;
}

bool ItemsPanel::useItem(ItemType type)
{
    for (auto &item : items) {
        if (item.type == type && item.quantity > 0) {
            item.quantity--;
            emit itemUsed(type); // 发送道具被使用的信号
            return true; // 使用成功
        }
    }
    return false; // 没有找到该道具或者数量不足
}
