#pragma once
#include <iostream>
#include "model.h"
using namespace std;

class ViewModel {
public:
    ViewModel(Model& model) : model(model) {}

    //主菜单界面
    //加载主菜单界面，包括从保存点继续、开始新的简单模式、开始新的困难模式、查看排行榜和退出游戏的按钮
    void loadMainMenu();
    //开始简单模式游戏
    void startSimpleMode();
    //开始困难模式游戏
    void startHardMode();
    //查看排行榜
    void viewLeaderboard();
    //退出游戏
    void exitGame();

    //难度设计与管理
    //检查是否创造新纪录，difficulty给出简单/困难模式
    void checkNewRecord(const std::string& difficulty);
    //显示鼓励界面（含难度显示）
    void displayEncouragement(const std::string& difficulty);

    //消除和非法操作(交换后无法消除）
    //交换两个元素的位置，包含非法交换（position代表坐标）
    //非法交换没有实现两次交换，而是直接无法交换并弹出提示框
    void swapElements(const std::pair<int, int>& position1, const std::pair<int, int>& position2);
    //更新游戏状态，包含得分、剩余步数、剩余时间、当前任务状态、交换操作是否合法、需要更新的坐标及更新信息
    void updateGameState();

    //任务
    //分配任务
    void assignNewTask();
    //完成任务后更新剩余步数和道具数量，rewardChoice为玩家选择的奖励
    void completeTask(const std::string& rewardChoice);

    //道具
    //使用道具，toolType为道具类型，position为操作位置的坐标
    void useTool(const std::string& toolType, const std::pair<int, int>& position);

    //保存
    //保存当前游戏状态
    void saveGameState();
    //加载保存的游戏状态
    void loadSavedGame();

private:
    Model& model;
}; 
