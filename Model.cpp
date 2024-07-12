// model.cpp
#include "model.h"

//构建10*10的板子
Model::Model(QObject *parent)
        : QObject(parent)
{
    m_board.resize(10);
    for (auto &row : m_board) {
        row.resize(10);
    }
}

Model::~Model()
{
}

//随机初始化板子，发送板子状态改变信号
void Model::initializeBoard()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            generateRandomColor(i, j);
        }
    }
    emit boardStateChanged();
}

//返回板子状态
QVector<QVector<int>> Model::getBoardState() const
{
    return m_board;
}

//交换两格元素，发出格子交换的信号
void Model::swapTiles(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= 10 || y1 < 0 || y1 >= 10 || x2 < 0 || x2 >= 10 || y2 < 0 || y2 >= 10) {
        //超出游戏板边界，交换非法
        return;
    }
    if (qAbs(x1 - x2) + qAbs(y1 - y2) != 1) {
        return; // 非相邻位置，交换非法
    }
    std::swap(m_board[x1][y1], m_board[x2][y2]);
    emit tilesSwapped();
}

//寻找当前棋盘中是否有可以消除的组合
bool Model::checkForMatches()
{
    bool matchFound = false;
    // Check rows
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] == m_board[i][j + 1] && m_board[i][j + 1] == m_board[i][j + 2]) {
                matchFound = true;
                // Add logic to collect tiles to eliminate here
            }
        }
    }
    // Check columns
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (m_board[i][j] == m_board[i + 1][j] && m_board[i + 1][j] == m_board[i + 2][j]) {
                matchFound = true;
                // Add logic to collect tiles to eliminate here
            }
        }
    }
    return matchFound;
}

//将可以消除的格子坐标{x，y}传入matches容器
void Model::checkForMatches(QVector<TilePosition>& matches)
{
    matches.clear();

    // 检查水平方向的匹配
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] == m_board[i][j + 1] && m_board[i][j + 1] == m_board[i][j + 2]) {
                matches.push_back({i, j});
                matches.push_back({i, j + 1});
                matches.push_back({i, j + 2});
            }
        }
    }

    // 检查垂直方向的匹配
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (m_board[i][j] == m_board[i + 1][j] && m_board[i + 1][j] == m_board[i + 2][j]) {
                matches.push_back({i, j});
                matches.push_back({i + 1, j});
                matches.push_back({i + 2, j});
            }
        }
    }
}

//对标记为要清除的格子进行消除（置EMPTY），发出信号传递被消除的格子坐标
void Model::eliminateTiles(const QVector<TilePosition>& tiles)
{
    for (const auto& tile : tiles) {
        m_board[tile.row][tile.col] = 0; 
    }
    emit tilesEliminated(tiles);
}

//对格子进行重力下落处理，传递格子下落的信号
void Model::applyGravity()
{
    // 从左往右每一列
    for (int j = 0; j < 10; ++j) {
        int emptyCount = 0; // 统计空位数量

        // 从底部往上遍历
        for (int i = 9; i >= 0; --i) {
            if (board[i][j] == 0) {
                emptyCount++;
            }
            else if (emptyCount > 0) {
                // 如果当前位置非空且下方有空位，执行下落操作
                std::swap(board[i][j], board[i + emptyCount][j]);
            }
        }
    }
    emit tilesDropped();
}

//
void Model::fillGaps()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (m_board[i][j] == 0) { // 如果方块为空
                int color = QRandomGenerator::global()->bounded(1, 7); // 随机生成颜色
                // 检查相邻方块的颜色，确保新颜色与下左右不同
                while (
                        (i > 0 && m_board[i - 1][j] == color) ||
                        (i < 9 && m_board[i + 1][j] == color) ||
                        (j < 9 && m_board[i][j + 1] == color)
                        ) {
                    color = QRandomGenerator::global()->bounded(1, 7);
                }
                m_board[i][j] = color;
            }
        }
    }
    emit boardUpdated();
}

void Model::updateBoardState()
{
    emit boardStateChanged();
}

void Model::generateRandomColor(int& x, int& y)
{
    int color = QRandomGenerator::global()->bounded(1, 7);
    while (color == (x > 0 ? m_board[x - 1][y] : 0) ||
           color == (x < 9 ? m_board[x + 1][y] : 0) ||
           color == (y > 0 ? m_board[x][y - 1] : 0)) {
        color = QRandomGenerator::global()->bounded(1, 7);
    }
    m_board[x][y] = color;
}