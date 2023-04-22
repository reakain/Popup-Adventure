#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "level.h"
#include "game.h"
#include "choice.h"
#include "story.h"

class PopUpWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PopUpWindow(QWidget *parent = nullptr);

    void OpenCurrentLevel();
    void UpdateLevel(QString goToName);
    void OpenHelp();
    void CloseSave();
    void show();
    QMessageBox::StandardButtons CheckSpecialCaseButtons();

//signals:

private:
    Level mLastLevel;
    Level mCurrentLevel;
    Level mHelp;
    Game mSaveData;
    Story mGameData;

};

#endif // POPUPWINDOW_H
