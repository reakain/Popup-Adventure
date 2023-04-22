#ifndef CHOICE_H
#define CHOICE_H
#include <QMessageBox>
#include <QMetaEnum>
#include <QJsonObject>

/*
 * Class for defining what an individual pop up window button does.
 */


class Choice
{
public:
    Choice() = default;
    explicit Choice(const QString &goToName);
    explicit Choice(const QString &goToName, const QMessageBox::StandardButton &button);

    /* Required, as it defines the level name to move to for the text
     * We do have some special characters though:
     * LastLevel: go to the last level we were on
     * Close: Save and exit application
     * Help: open the application information
    */
    QString goToName() const;

    // If not defined, defaults to Ok button
    QMessageBox::StandardButton button() const;

    // These are used to read from our json story file
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString mGoToName;
    QMessageBox::StandardButton mButton;
};

#endif // CHOICE_H
