// SettingsView.h
#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SettingsView : public QWidget
{
Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView();

signals:
    void continueEasyMode();
    void continueHardMode();
    void startNewEasyMode();
    void startNewHardMode();
    void saveAndExit();

private:
    QVBoxLayout *_layout;
    QPushButton *_continueEasyButton;
    QPushButton *_continueHardButton;
    QPushButton *_newEasyButton;
    QPushButton *_newHardButton;
    QPushButton *_saveAndExitButton;
};

#endif // SETTINGSVIEW_H