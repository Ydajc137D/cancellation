// LeaderboardView.cpp
#include "LeaderboardView.h"

LeaderboardView::LeaderboardView(QWidget *parent)
        : QWidget(parent), _layout(new QVBoxLayout)
{
    // 创建按钮
    _easyModeRankingButton = new QPushButton("显示简单模式排行榜");
    _hardModeRankingButton = new QPushButton("显示困难模式排行榜");

    // 添加按钮到布局中
    _layout->addWidget(_easyModeRankingButton);
    _layout->addWidget(_hardModeRankingButton);

    // 设置布局
    this->setLayout(_layout);

    // 连接信号和槽
    connect(_easyModeRankingButton, &QPushButton::clicked, this, &LeaderboardView::onShowEasyModeRankingClicked);
    connect(_hardModeRankingButton, &QPushButton::clicked, this, &LeaderboardView::onShowHardModeRankingClicked);
}

LeaderboardView::~LeaderboardView()
{
    delete _layout;
}

void LeaderboardView::onShowEasyModeRankingClicked()
{
    emit showEasyModeRankingRequested();
}

void LeaderboardView::onShowHardModeRankingClicked()
{
    emit showHardModeRankingRequested();
}