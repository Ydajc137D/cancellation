#include "gameview.h"
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QIcon>

GameView::GameView(QWidget *parent) : QWidget(parent),
    gameBoardLayout(nullptr),
    itemsPanel(nullptr),
    score(0),
    animationTimer(nullptr)
{
    initGameView();
}

void GameView::startNewGame()
{
    // 初始化游戏板和其他必要的组件，以便开始新游戏
    initGameBoard();
    score = 0;
    
    // 启动任何初始动画或定时器
    startInitialAnimations();
}


void GameView::handleItemUsed(ItemType type)
{
    qDebug() << "Item used: " << type;
}

void GameView::initGameView()
{
    // 创建游戏板布局
    gameBoardLayout = new QGridLayout(this);
    setLayout(gameBoardLayout);

    // 连接信号和槽的示例
    // 假设 itemsPanel 已经在其他地方实例化并适当连接
    itemsPanel = new ItemsPanel(this);
    connect(itemsPanel, &ItemsPanel::itemUsed, this, &GameView::handleItemUsed);

    // 初始化动画定时器的示例
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &GameView::animateElimination);

    // 开始新游戏的函数调用
    startNewGame();
}


void GameView::initGameBoard()
{
    const int rows = 10;
    const int cols = 10;
    gameBoard.resize(rows);

    for (int i = 0; i < rows; ++i) {
        gameBoard[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            gameBoard[i][j] = new QLabel(this);
            gameBoard[i][j]->setText(QString::number(i * cols + j));
            gameBoard[i][j]->setFixedSize(100, 100);
            gameBoardLayout->addWidget(gameBoard[i][j], i, j);
            connect(gameBoard[i][j], &QLabel::clicked, this, [this, i, j]() {
                handleClick(i, j);
            });
        }
    }
}

void GameView::handleClick(int row, int col)
{
    qDebug() << "点击了第" << row << "行，第" << col << "列";

    // 检查是否有有效的点击
    if (!isValidClick(row, col)) {
        qDebug() << "无效的点击或该位置不可点击";
        return;
    }

    // 选择当前点击的方块
    selectBlock(row, col);

    // 检查是否有可消除的方块
    if (checkForMatches()) {
        // 执行消除操作
        removeMatches();
        
        // 更新分数
        updateScore();

        // 检查并执行掉落动画和新方块生成
        handleBlockFalling();

        // 检查是否有新的可消除方块
        while (checkForMatches()) {
            removeMatches();
            updateScore();
            handleBlockFalling();
        }
    } else {
        // 没有可消除的方块，取消选择当前方块
        deselectBlock(row, col);
    }

    // 检查游戏是否结束
    if (checkGameOver()) {
        handleGameOver();
    }
}


void GameView::eliminateItems()
{
    QList<QPoint> itemsToRemove; // 存储需要移除的物品位置列表

    // 遍历游戏板以找到匹配项
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // 检查当前物品是否有匹配（水平或垂直）
            if (hasMatchAt(row, col)) {
                // 将当前物品的位置添加到移除列表中
                itemsToRemove.append(QPoint(row, col));
            }
        }
    }

    // 处理需要移除的物品
    for (const QPoint &pos : itemsToRemove) {
        int row = pos.x();
        int col = pos.y();

        // 执行移除 (row, col) 处的物品
        gameBoard[row][col].removeFromBoard();

        // 在移除后，处理特效或动画
        gameBoard[row][col].playRemovalAnimation();
    }

    // 消除物品后，重新填充游戏板
    refillBoard();

    //更新分数
    updateScore();
}



void GameView::updateScore(int points)
{
    score += points;
    qDebug() << "Score updated: " << score;

    // 检查是否触发游戏结束条件
    checkGameOver();
}


void GameView::checkGameOver()
{
    if (score <= 0) {
        qDebug() << "Game over! Your score is zero.";
        // 可以在此处触发游戏结束操作，例如显示游戏结束界面或重新开始游戏
    }
}

