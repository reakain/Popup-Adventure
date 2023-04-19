#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "level.h"
#include "game.h"

class PopUpWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PopUpWindow(QWidget *parent = nullptr);

signals:

private:
    Level mLastLevel;
    Level mCurrentLevel;
    Game mGameData;

};

#endif // POPUPWINDOW_H
