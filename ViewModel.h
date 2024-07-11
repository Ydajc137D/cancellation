#pragma once
#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "Model.h"

class ViewModel {
public:
    ViewModel();

    // 开始新游戏
    void saveAndResetSimple();
    void saveAndResetDifficult();

    // 排行榜
    void getSimpleRank();
    void getDifficultRank();

    // 游戏状态管理
    void fetchUserSwap(int x1, int y1, int x2, int y2);
    GameState getGameState() const;
    std::vector<std::vector<ElementType>> getBoardState() const;
    int getScoreState() const;
    int getStepsLeftState() const;
    std::string getTaskState() const;
    std::unordered_map<ToolType, int> getToolState() const;
    bool isGameOver();

    // 道具操作
    void getToolUse(ToolType tool, int x, int y);

    // 任务管理
    int getNewTask() const;
    void fetchUpdateTaskProgress();

    // 进度管理
    void saveGameProgress();
    void loadGameProgress();

    // 积分和记录管理
    int fetchPoint() const;
    bool getIsNewRecord();

private:
    Model model;
};

#endif