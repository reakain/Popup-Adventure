#include "popupwindow.h"

PopUpWindow::PopUpWindow(QWidget *parent) : QMainWindow(parent)
{
    /*
     * Let's first see if there's save data to load, and load out whole ass logic tree script
     *
     */
    mGameData.loadGame(Game::SaveFormat::Json);


    //mGameData.read("")
    QMessageBox msgBox;
    msgBox.setText("Welcome to the adventure!");
    msgBox.setInformativeText("Do you want to start a new game?");
    // If they don't have save data, the no option shouldn't be present
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Close | QMessageBox::Help);
    // If we have save data, the default should be no
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        // Start a new game
        break;
    case QMessageBox::No:
        // Ask if they want to continue a game
        break;
    case QMessageBox::Close:
        // Exit the application
        //QApplication::exit();
        //this->close();
        break;
    case QMessageBox::Help:
        // Popup info about the application
        //int ret = QMessageBox::information(this, tr("About Popup Adventure"), tr("Popup Adventure is a text adventure game, delivered through the wildly popular modality of popup messages!"), QMessageBox::Ok);
        OpenHelp();
        break;
    }
}

void PopUpWindow::OpenCurrentLevel()
{
    QMessageBox msgBox;
    msgBox.setText(mCurrentLevel.titleText());
    msgBox.setInformativeText(mCurrentLevel.bodyText());
    msgBox.setIcon(mCurrentLevel.icon());
    QList<Choice> choices = mCurrentLevel.choices();
    if(choices.length() < 1)
        msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Help);
    else
    {
        QMessageBox::StandardButtons choiceSet = choices[0].button();
        if(choices.length() > 1)
        {
            for(int i = 1; i < choices.length(); i++)
            {
                choiceSet = choiceSet | choices[i].button();
            }
        }
        choiceSet = choiceSet | QMessageBox::Close | QMessageBox::Help;
        msgBox.setStandardButtons(choiceSet);
    }
    int ret = msgBox.exec();
    Choice pickedChoice;
    switch(ret)
    {
    case QMessageBox::Yes:
        mCurrentLevel.getChoiceOfType(QMessageBox::Yes, pickedChoice);
        break;
    case QMessageBox::No:
        mCurrentLevel.getChoiceOfType(QMessageBox::No, pickedChoice);
        break;
    case QMessageBox::Cancel:
        mCurrentLevel.getChoiceOfType(QMessageBox::Cancel, pickedChoice);
        break;
    case QMessageBox::Ok:
        mCurrentLevel.getChoiceOfType(QMessageBox::Ok, pickedChoice);
        break;
    case QMessageBox::YesToAll:
        mCurrentLevel.getChoiceOfType(QMessageBox::YesToAll, pickedChoice);
        break;
    case QMessageBox::NoToAll:
        mCurrentLevel.getChoiceOfType(QMessageBox::NoToAll, pickedChoice);
        break;
    case QMessageBox::Abort:
        mCurrentLevel.getChoiceOfType(QMessageBox::Abort, pickedChoice);
        break;
    case QMessageBox::Open:
        mCurrentLevel.getChoiceOfType(QMessageBox::Open, pickedChoice);
        break;
    case QMessageBox::Save:
        mCurrentLevel.getChoiceOfType(QMessageBox::Save, pickedChoice);
        break;
    case QMessageBox::Apply:
        mCurrentLevel.getChoiceOfType(QMessageBox::Apply, pickedChoice);
        break;
    case QMessageBox::Reset:
        mCurrentLevel.getChoiceOfType(QMessageBox::Reset, pickedChoice);
        break;
    case QMessageBox::Retry:
        mCurrentLevel.getChoiceOfType(QMessageBox::Retry, pickedChoice);
        break;
    case QMessageBox::Ignore:
        mCurrentLevel.getChoiceOfType(QMessageBox::Ignore, pickedChoice);
        break;
    case QMessageBox::Discard:
        mCurrentLevel.getChoiceOfType(QMessageBox::Discard, pickedChoice);
        break;
    case QMessageBox::SaveAll:
        mCurrentLevel.getChoiceOfType(QMessageBox::SaveAll, pickedChoice);
        break;
    case QMessageBox::RestoreDefaults:
        mCurrentLevel.getChoiceOfType(QMessageBox::RestoreDefaults, pickedChoice);
        break;
    case QMessageBox::Close:
        CloseSave();
        break;
    case QMessageBox::Help:
        // Popup info about the application
        OpenHelp();
        break;
    }
}

void PopUpWindow::OpenHelp()
{
    QMessageBox::information(this, tr("About Popup Adventure"), tr("Popup Adventure is a text adventure game, delivered through the wildly popular modality of popup messages!"), QMessageBox::Ok);
    // Return to current level
    OpenCurrentLevel();
}

void PopUpWindow::CloseSave()
{
    mGameData.saveGame(Game::SaveFormat::Json);
    this->close();
}

