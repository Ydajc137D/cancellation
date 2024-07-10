// GameMainWindow.h
#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class GameView;
class SettingsView;
class LeaderboardView;

class GameMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameMainWindow(QWidget *parent = nullptr);
    ~GameMainWindow();

    void changeToGameView();
    void changeToSettingsView();
    void changeToLeaderboardView();
    void showNewRecordEncouragement(int mode);

private:
    QStackedWidget *_stackedWidget;
    GameView *_gameView;
    SettingsView *_settingsView;
    LeaderboardView *_leaderboardView;
};
#endif // GAMEMAINWINDOW_H