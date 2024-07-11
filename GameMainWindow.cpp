#include "GameMainWindow.h"
#include "GameView.h"
#include "SettingsView.h"
#include "LeaderboardView.h"
#include <QMessageBox>
#include <QApplication>

GameMainWindow::GameMainWindow(QWidget *parent)
        : QMainWindow(parent),
          _stackedWidget(new QStackedWidget(this)),
          _gameView(nullptr),
          _settingsView(nullptr),
          _leaderboardView(nullptr)
{
    // 初始化主窗口布局
    this->setCentralWidget(_stackedWidget);

    // 创建并初始化子视图
    _gameView = new GameView(this);
    _settingsView = new SettingsView(this);
    _leaderboardView = new LeaderboardView(this);

    // 将子视图添加到堆叠小部件中
    _stackedWidget->addWidget(_gameView);
    _stackedWidget->addWidget(_settingsView);
    _stackedWidget->addWidget(_leaderboardView);
}

GameMainWindow::~GameMainWindow()
{
    delete _stackedWidget;
    delete _gameView;
    delete _settingsView;
    delete _leaderboardView;
}

void GameMainWindow::changeToGameView()
{
    // 切换到游戏视图
    _stackedWidget->setCurrentWidget(_gameView);
}

void GameMainWindow::changeToSettingsView()
{
    // 切换到设置视图
    _stackedWidget->setCurrentWidget(_settingsView);
}

void GameMainWindow::changeToLeaderboardView()
{
    // 切换到排行榜视图
    _stackedWidget->setCurrentWidget(_leaderboardView);
}

void GameMainWindow::setGameView(GameView *view)
{
    _gameView = view;
}

void GameMainWindow::setSettingsView(SettingsView *view)
{
    _settingsView = view;
}

void GameMainWindow::setLeaderboardView(LeaderboardView *view)
{
    _leaderboardView = view;
}

QStackedWidget *GameMainWindow::getStackedWidget()
{
    return _stackedWidget;
}

void GameMainWindow::showNewRecordEncouragement(int mode)
{
    // 显示新纪录鼓励界面
    if (mode == 0) // 简单模式
    {
        QMessageBox::information(this, "新纪录！", "恭喜！您刚刚创造了简单模式的新纪录！");
    }
    else if (mode == 1) // 困难模式
    {
        QMessageBox::information(this, "新纪录！", "恭喜！您刚刚创造了困难模式的新纪录！");
    }
}