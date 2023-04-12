#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

class PopUpWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PopUpWindow(QWidget *parent = nullptr);

signals:

};

#endif // POPUPWINDOW_H
