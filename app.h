// App.h
#ifndef APP_H
#define APP_H

#include <QObject>
#include "GameView.h"
#include "GameMainWindow.h"
#include "LeaderboardView.h"
#include "SettingsView.h"
#include "ViewModel.h"

class App : public QObject
{
Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
    ~App();

    void init();

public slots:
    void onContinueEasyMode();
    void onContinueHardMode();
    void onStartNewEasyMode();
    void onStartNewHardMode();
    void onSaveAndExit();

private:
    GameView *m_gameView;
    SettingsView *m_settingsView;
    LeaderboardView *m_leaderboardView;
    ViewModel *m_viewModel;
    GameMainWindow *m_mainWindow;
};

#endif // APP_H