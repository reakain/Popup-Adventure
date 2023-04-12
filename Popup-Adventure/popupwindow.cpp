#include "popupwindow.h"

PopUpWindow::PopUpWindow(QWidget *parent) : QMainWindow(parent)
{
    /*
     * Let's first see if there's save data to load, and load out whole ass logic tree script
     *
     */
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
        int ret = QMessageBox::information(this, tr("About Popup Adventure"), tr("Popup Adventure is a text adventure game, delivered through the wildly popular modality of popup messages!"), QMessageBox::Ok);
        break;
    }
}

