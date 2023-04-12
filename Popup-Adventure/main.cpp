#include "mainwindow.h"
#include "popupwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Popup-Adventure_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //MainWindow w;
    //w.show();
    PopUpWindow w;
    //w.show();
    /* If we just handle levels here instead...
     * String currentLevel = "Start";
     *
     */

    return a.exec();
    //return 0;
}
