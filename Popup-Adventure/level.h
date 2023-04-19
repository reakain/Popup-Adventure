#ifndef LEVEL_H
#define LEVEL_H

#include "choice.h"
#include <QJsonObject>
#include <QList>
#include <QMessageBox>

/*
 * Class for defining what each pop up box displays. Reads data from json
 */

class Level
{
public:
    Level() = default;
    explicit Level(const QString &name);

    QString name() const;
    QString titleText() const;
    QString bodyText() const;

    /* Default if not provided is information. Values to use in json are:
     * NoIcon	    0
     * Question	    4
     * Information	1
     * Warning	    2
     * Critical	    3
    */
    QMessageBox::Icon icon() const;

    // The list of button response options
    QList<Choice> choices() const;
    void setChoices(const QList<Choice> &choices);

    // Reading from json
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString mName;
    QString mTitleText;
    QString mBodyText;
    QMessageBox::Icon mIcon;
    QList<Choice> mChoices;
};

#endif // LEVEL_H
