// LeaderboardView.h
#ifndef LEADERBOARDVIEW_H
#define LEADERBOARDVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LeaderboardView : public QWidget
{
Q_OBJECT
public:
    explicit LeaderboardView(QWidget *parent = nullptr);
    ~LeaderboardView();

signals:
    void showEasyModeRankingRequested();
    void showHardModeRankingRequested();

private slots:
    void onShowEasyModeRankingClicked();
    void onShowHardModeRankingClicked();

private:
    QVBoxLayout *_layout;
    QPushButton *_easyModeRankingButton;
    QPushButton *_hardModeRankingButton;
};

#endif // LEADERBOARDVIEW_H