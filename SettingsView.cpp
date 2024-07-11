// SettingsView.cpp
#include "SettingsView.h"

SettingsView::SettingsView(QWidget *parent)
        : QWidget(parent), _layout(new QVBoxLayout)
{
    // 创建按钮
    _continueEasyButton = new QPushButton("从上一个简单模式保存点继续", this);
    _continueHardButton = new QPushButton("从上一个困难模式保存点继续", this);
    _newEasyButton = new QPushButton("保存并开始新的一局简单模式游戏", this);
    _newHardButton = new QPushButton("保存并开始新的一局困难模式游戏", this);
    _saveAndExitButton = new QPushButton("保存并退出", this);

    // 添加按钮到布局中
    _layout->addWidget(_continueEasyButton);
    _layout->addWidget(_continueHardButton);
    _layout->addWidget(_newEasyButton);
    _layout->addWidget(_newHardButton);
    _layout->addWidget(_saveAndExitButton);

    // 设置布局
    this->setLayout(_layout);

    // 连接信号和槽
    connect(_continueEasyButton, &QPushButton::clicked, this, &SettingsView::continueEasyMode);
    connect(_continueHardButton, &QPushButton::clicked, this, &SettingsView::continueHardMode);
    connect(_newEasyButton, &QPushButton::clicked, this, &SettingsView::startNewEasyMode);
    connect(_newHardButton, &QPushButton::clicked, this, &SettingsView::startNewHardMode);
    connect(_saveAndExitButton, &QPushButton::clicked, this, &SettingsView::saveAndExit);
}

SettingsView::~SettingsView()
{
    delete _layout;
}




