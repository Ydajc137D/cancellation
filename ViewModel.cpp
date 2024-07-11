#include "ViewModel.h"

ViewModel::ViewModel() : model() {}

void ViewModel::saveAndResetSimple() {
    model.saveGame();
    model.initializeGame(EASY);
}

void ViewModel::saveAndResetDifficult() {
    model.saveGame();
    model.initializeGame(HARD);
}

void ViewModel::getSimpleRank() {
    // 获取简单模式排行榜
    model.loadLeaderboard();
}

void ViewModel::getDifficultRank() {
    // 获取困难模式排行榜
    model.loadLeaderboard();
}

void ViewModel::fetchUserSwap(int x1, int y1, int x2, int y2) {
    if (model.isValidSwap(x1, y1, x2, y2)) {
        model.processSwap(x1, x2, y1, y2);
    }
    else {
        // 处理非法交换
        std::swap(model.board[x1][y1], model.board[x2][y2]);
        std::swap(model.board[x1][y1], model.board[x2][y2]);
    }
}

GameState ViewModel::getGameState() const {
    return model.getGameState();
}

void ViewModel::getToolUse(ToolType tool, int x, int y) {
    model.useTool(tool, x, y);
}

//int ViewModel::getNewTask() const {
//    return model.getGameState().currentTask.TaskType;
//}

void ViewModel::fetchUpdateTaskProgress() {
    if (model.checkTaskCompletion()) {
        model.assignNewTask();
    }
}

void ViewModel::saveGameProgress() {
    model.saveGame();
}

void ViewModel::loadGameProgress() {
    model.loadGame();
}

int ViewModel::fetchPoint() const {
    return model.getGameState().score;
}

bool ViewModel::getIsNewRecord() {
    return model.BreakRecord();
}

bool ViewModel::isGameOver() {
    return model.isGameOver();
}