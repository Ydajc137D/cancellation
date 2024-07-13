#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "gameview.h"
#include "itemspanel.h"
#include "taskspanel.h"
#include "scoremanager.h"
#include "difficultyselector.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGameView();
    void showItemsPanel();
    void showTasksPanel();
    void showScoreManager();
    void showDifficultySelector();

private:
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void setupCentralWidget();

    QStackedWidget *stackedWidget;
    GameView *gameView;
    ItemsPanel *itemsPanel;
    TasksPanel *tasksPanel;
    ScoreManager *scoreManager;
    DifficultySelector *difficultySelector;

    QAction *gameViewAction;
    QAction *itemsPanelAction;
    QAction *tasksPanelAction;
    QAction *scoreManagerAction;
    QAction *difficultySelectorAction;

    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
