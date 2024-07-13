#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Main Window");

    createMenuBar();
    createToolBar();
    createStatusBar();
    setupCentralWidget();
}

MainWindow::~MainWindow()
{
    // Destructor
}

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *viewMenu = menuBar->addMenu(tr("View"));

    gameViewAction = new QAction(tr("Game View"), this);
    connect(gameViewAction, &QAction::triggered, this, &MainWindow::showGameView);
    viewMenu->addAction(gameViewAction);

    itemsPanelAction = new QAction(tr("Items Panel"), this);
    connect(itemsPanelAction, &QAction::triggered, this, &MainWindow::showItemsPanel);
    viewMenu->addAction(itemsPanelAction);

    tasksPanelAction = new QAction(tr("Tasks Panel"), this);
    connect(tasksPanelAction, &QAction::triggered, this, &MainWindow::showTasksPanel);
    viewMenu->addAction(tasksPanelAction);

    QMenu *toolsMenu = menuBar->addMenu(tr("Tools"));

    scoreManagerAction = new QAction(tr("Score Manager"), this);
    connect(scoreManagerAction, &QAction::triggered, this, &MainWindow::showScoreManager);
    toolsMenu->addAction(scoreManagerAction);

    difficultySelectorAction = new QAction(tr("Difficulty Selector"), this);
    connect(difficultySelectorAction, &QAction::triggered, this, &MainWindow::showDifficultySelector);
    toolsMenu->addAction(difficultySelectorAction);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    toolBar->addAction(gameViewAction);
    toolBar->addAction(itemsPanelAction);
    toolBar->addAction(tasksPanelAction);
    toolBar->addSeparator();
    toolBar->addAction(scoreManagerAction);
    toolBar->addAction(difficultySelectorAction);
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel("Ready", this);
    statusBar()->addWidget(statusLabel);
}

void MainWindow::setupCentralWidget()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    gameView = new GameView(this);
    itemsPanel = new ItemsPanel(this);
    tasksPanel = new TasksPanel(this);
    scoreManager = new ScoreManager(this);
    difficultySelector = new DifficultySelector(this);

    stackedWidget->addWidget(gameView);
    stackedWidget->addWidget(itemsPanel);
    stackedWidget->addWidget(tasksPanel);
    stackedWidget->addWidget(scoreManager);
    stackedWidget->addWidget(difficultySelector);
}

void MainWindow::showGameView()
{
    stackedWidget->setCurrentWidget(gameView);
    statusLabel->setText("Game View");
}

void MainWindow::showItemsPanel()
{
    stackedWidget->setCurrentWidget(itemsPanel);
    statusLabel->setText("Items Panel");
}

void MainWindow::showTasksPanel()
{
    stackedWidget->setCurrentWidget(tasksPanel);
    statusLabel->setText("Tasks Panel");
}

void MainWindow::showScoreManager()
{
    stackedWidget->setCurrentWidget(scoreManager);
    statusLabel->setText("Score Manager");
}

void MainWindow::showDifficultySelector()
{
    stackedWidget->setCurrentWidget(difficultySelector);
    statusLabel->setText("Difficulty Selector");
}
