#include "popupwindow.h"

PopUpWindow::PopUpWindow(QWidget *parent) : QMainWindow(parent)
{




    //mGameData.getLevelWithName("Title", mCurrentLevel);
    //OpenCurrentLevel();

}


int PopUpWindow::FindStoryFiles(QList<Story> &stories)
{
    QDir dir;
       dir.setFilter(QDir::Files | QDir::Readable | QDir::NoSymLinks);
       dir.setSorting(QDir::Name);
       dir.setNameFilters(QStringList()<<"story_*.json");

       QStringList fileList = dir.entryList();
       for(int i=0; i < fileList.size(); i++)
       {
           stories.append(Story());
           if(!stories[stories.count()-1].loadStory(fileList[i]))
           {
               stories.removeLast();
           }
       }
       return stories.size();
}

void PopUpWindow::show()
{
    /*
     * Let's first see if there's save data to load, and load out whole ass logic tree script
     *
     */
    // Let's look for story files
    QList<Story> stories;
    int ret = FindStoryFiles(stories);
    if(ret == 0) {
        // No stories loaded, close
        this->close();
        return;
    }
    else if(ret == 1) {
        // Only one story loaded, make that our story and run it
        mGameData = stories[0];
        mGameData.getLevelWithName("Help", mHelp);
        mGameData.getLevelWithName("Title", mCurrentLevel);
        OpenCurrentLevel();
    }
    else
    {
        // Multiple stories found, so we need to have the user pick one.
        int story_ret = QMessageBox::No;
        int i = 0;
        //for(int i = 0; i < ret; i++)
        while(story_ret == QMessageBox::No)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(stories[i].title());
            QString bodyText = "Would you like to play ";
            bodyText.append(stories[i].title());
            bodyText.append("?");
            msgBox.setText(bodyText);
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);
            story_ret = msgBox.exec();
            if(story_ret == QMessageBox::Yes)
            {
                mGameData = stories[i];
                mGameData.getLevelWithName("Help", mHelp);
                mGameData.getLevelWithName("Title", mCurrentLevel);
                OpenCurrentLevel();
            }
            else if(story_ret == QMessageBox::Close)
            {
                this->close();
                return;
            }
            else
            {
                i++;
                if( i >= ret)
                {
                    i = 0;
                }
            }
        }

    }
    // Let's load up our actual narrative


}

QMessageBox::StandardButtons PopUpWindow::CheckSpecialCaseButtons()
{
    
    if(mCurrentLevel.name() == "NewGame")
    {
        // Then let's load our save data
        if(mSaveData.loadGame(Game::SaveFormat::Json))
        {
            StorySave newSave;
            if(mSaveData.getGameSave(newSave, mGameData.title()))
            {
            // Then we had save data, so let's offer to continue
            //mGameData.getLevelWithName()
            QList<Choice> choices = mCurrentLevel.choices();
            //choices.add(Choice("Start", QMessageBox::Yes));
            choices.append(Choice(newSave.currentLevel(), QMessageBox::No));
            mCurrentLevel.setChoices(choices);
            return QMessageBox::Yes | QMessageBox::No | QMessageBox::Close | QMessageBox::Help;
            }
            else
            {
                return QMessageBox::Yes | QMessageBox::Close | QMessageBox::Help;
            }
        }
        else
        {
            // Otherwise let's just start a new game
            //mGameData.getLevelWithName("Start", mCurrentLevel);
            //OpenCurrentLevel();
            return QMessageBox::Yes | QMessageBox::Close | QMessageBox::Help;
        }
    }
    else
    {
        QList<Choice> choices = mCurrentLevel.choices();
        if(choices.length() < 1)
            return QMessageBox::Close | QMessageBox::Help;
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
            return choiceSet;
        }
    }
}

void PopUpWindow::OpenCurrentLevel()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(mCurrentLevel.titleText());
    msgBox.setText(mCurrentLevel.bodyText());
    msgBox.setIcon(mCurrentLevel.icon());
    msgBox.setStandardButtons(CheckSpecialCaseButtons());
    // Qt auto links the esc/x button to the appropriate reject mode button like close or cancel
    // If we don't provide a close/cancel button, then the x is disabled >.>
    // We tried to just hide our close button, but Qt no longer likes that, for some reason
    QAbstractButton *pCloseBtn = msgBox.button(QMessageBox::Close);
    //pCloseBtn->hide();
    //QPushButton *pCloseBtn = msgBox.addButton(QMessageBox::Close);
    //pCloseBtn->setVisible(false);

    /*
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
    */
    int ret = msgBox.exec();
    Choice pickedChoice;
    switch(ret)
    {
    case QMessageBox::Yes:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Yes, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::No:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::No, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Cancel:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Cancel, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Ok:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Ok, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::YesToAll:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::YesToAll, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::NoToAll:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::NoToAll, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Abort:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Abort, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Open:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Open, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Save:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Save, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Apply:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Apply, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Reset:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Reset, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Retry:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Retry, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Ignore:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Ignore, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::Discard:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::Discard, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::SaveAll:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::SaveAll, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
        break;
    case QMessageBox::RestoreDefaults:
        if(mCurrentLevel.getChoiceOfType(QMessageBox::RestoreDefaults, pickedChoice))
        {
            UpdateLevel(pickedChoice.goToName());
        }
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

void PopUpWindow::UpdateLevel(QString goToName)
{
    mLastLevel = mCurrentLevel;
    if(mGameData.getLevelWithName(goToName,mCurrentLevel))
    {
        OpenCurrentLevel();
    }
    else
    {
        // Failed to find level with name. Suffer
    }
}

void PopUpWindow::OpenHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(mHelp.titleText());
    msgBox.setText(mHelp.bodyText());
    msgBox.setIcon(mHelp.icon());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    //QMessageBox::information(this, tr("About Popup Adventure"), tr("Popup Adventure is a text adventure game, delivered through the wildly popular modality of popup messages!"), QMessageBox::Ok);
    // Return to current level
    OpenCurrentLevel();
}

void PopUpWindow::CloseSave()
{
    QTextStream(stdout) << "Close Game Triggered\n";
    mSaveData.updateSave(mGameData.title(), mCurrentLevel.name());
    //mSaveData.setLevel(mCurrentLevel);
    mSaveData.saveGame(Game::SaveFormat::Json);
    this->close();
}

