#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <unordered_map>

enum Difficulty { EASY, HARD };
enum ElementType {
    EMPTY,
    APPLE,
    ORANGE,
    BANANA,
    PEACH,
    PINEAPPLE,
    GRAPE,
    ROW_CLEAR,
    COLUMN_CLEAR,
    BOMB,
    RAINBOW_CIRCLE
};
enum ToolType { HAMMER, BOMB_TRANSFORM, REFRESH, ROW_CLEAR_TRANSFORM, COLUMN_CLEAR_TRANSFORM };

struct GameState {
    std::vector<std::vector<ElementType>> board;
    int score;
    int stepsLeft;
    //int timeLeft;
    Task currentTask;
    bool isNewRecord;
    std::unordered_map<ToolType, int> ToolNumber;
};

struct Task {
    int TaskType;
    std::string Taskcontent;
};

class Model {
public:
    Model();

    // 初始化游戏状态
    void initializeGame(Difficulty difficulty);

    // 保存和加载游戏进度
    bool saveGame();
    bool loadGame();

    // 消除逻辑
    bool isValidSwap(int x1, int y1, int x2, int y2);
    void processSwap(int x1, int y1, int x2, int y2);
    void handleEmptyAndGravity();
    bool checkSpecialElement(int x, int y);
    bool checkRowOrColumn(int x, int y, bool isRow);
    bool checkRainbowCircle(int x, int y, ElementType type);
    bool checkBombL(int x, int y, ElementType type);
    bool checkBombT(int x, int y, ElementType type);
    bool checkRowClear(int x, int y, ElementType type);
    bool checkColumnClear(int x, int y, ElementType type);
    bool checkRow(int x, int y, ElementType type);
    bool checkColumn(int x, int y, ElementType type);
    //以下待补充
    //ps:特殊方块清场时不会清掉特殊方块
    void clearSpecialElement(ElementType type, int x, int y);
    void cleardoubleSpecialElements(ElementType type1, int x1, int y1, ElementType type2, int x2, int y2);

    void clearRowClear(int x, int y);
    void clearColumnClear(int x, int y);
    void clearBomb(int x, int y);
    void clearRainbowCircle(int x1, int y1, int x2, int y2);

    void RainbowCircle2RainbowCircle(int x1, int y1, int x2, int y2);//清屏
    void RainbowCircle2Bomb(int x1, int y1, int x2, int y2);//消7*7
    void RainbowCircle2RowClear(int x1, int y1, int x2, int y2);//消5行
    void RainbowCircle2ColumnClear(int x1, int y1, int x2, int y2);//消5列

    void Bomb2Bomb(int x1, int y1, int x2, int y2);//消5*5
    void Bomb2RowClear(int x1, int y1, int x2, int y2);//消3行
    void Bomb2ColumnClear(int x1, int y1, int x2, int y2);//消3列

    void Column2Row(int x1, int y1, int x2, int y2);//消十字
    void Column2Column(int x1, int y1, int x2, int y2);//消？？
    void Row2Row(int x1, int y1, int x2, int y2);//消？？

    // 道具逻辑
    void useTool(ToolType tool, int x, int y);//考虑道具剩余个数
    void useHammer(int x, int y);
    void useBombTran(int x, int y);
    void useRefresh(int x, int y);
    void useRow(int x, int y);
    void useColumn(int x, int y);

    // 任务逻辑
    void assignNewTask();
    bool checkTaskCompletion();

    // 排行榜管理
    void loadLeaderboard();
    void saveLeaderboard();
    bool BreakRecord();

    // 获取游戏状态
    GameState getGameState() const;
    bool isGameOver();

private:
    std::vector<std::vector<ElementType>> board;
    int score;
    int stepsLeft;
    //int timeLeft;
    Task currentTask;
    Difficulty currentDifficulty;
    std::unordered_map<Difficulty, int> highScores;
    bool isNewRecord;
    std::unordered_map<ToolType, int> ToolNumber;//每种道具剩余数量

    ElementType getRandomFruitType();
    void refreshBoard();
    void clearElements();
    void updateScore();

private:
    friend class ViewModel;
};

#endif