// App.cpp
#include "App.h"
#include "GameMainWindow.h"

App::App(QObject *parent)
        : QObject(parent),
          m_gameView(nullptr),
          m_settingsView(nullptr),
          m_leaderboardView(nullptr),
          m_viewModel(nullptr),
          m_mainWindow(nullptr)
{}

App::~App()
{
    delete m_gameView;
    delete m_settingsView;
    delete m_leaderboardView;
    delete m_viewModel;
    delete m_mainWindow;
}

void App::init()
{
    m_gameView = new GameView;
    m_settingsView = new SettingsView;
    m_leaderboardView = new LeaderboardView;
    m_viewModel = new ViewModel;

    m_gameView->setGameViewModel(reinterpret_cast<GameViewModel *>(m_viewModel));
    m_mainWindow = new GameMainWindow;

    m_mainWindow->setGameView(m_gameView);
    m_mainWindow->setSettingsView(m_settingsView);
    m_mainWindow->setLeaderboardView(m_leaderboardView);
    m_mainWindow->getStackedWidget()->addWidget(m_gameView);
    m_mainWindow->getStackedWidget()->addWidget(m_settingsView);
    m_mainWindow->getStackedWidget()->addWidget(m_leaderboardView);

    connect(m_settingsView, &SettingsView::continueEasyMode, this, &App::onContinueEasyMode);
    connect(m_settingsView, &SettingsView::continueHardMode, this, &App::onContinueHardMode);
    connect(m_settingsView, &SettingsView::startNewEasyMode, this, &App::onStartNewEasyMode);
    connect(m_settingsView, &SettingsView::startNewHardMode, this, &App::onStartNewHardMode);
    connect(m_settingsView, &SettingsView::saveAndExit, this, &App::onSaveAndExit);

    m_mainWindow->show();
}

void App::onContinueEasyMode()
{
    m_viewModel->saveAndResetSimple();
    m_mainWindow->changeToGameView();
}

void App::onContinueHardMode()
{
    m_viewModel->saveAndResetDifficult();
    m_mainWindow->changeToGameView();
}

void App::onStartNewEasyMode()
{
    m_viewModel->saveAndResetSimple();
    m_mainWindow->changeToGameView();
}

void App::onStartNewHardMode()
{
    m_viewModel->saveAndResetDifficult();
    m_mainWindow->changeToGameView();
}

void App::onSaveAndExit()
{
    m_viewModel->saveGameProgress();
    m_mainWindow->close();
}
