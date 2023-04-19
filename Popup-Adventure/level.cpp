#include "level.h"
// https://doc.qt.io/qt-6/qtcore-serialization-savegame-example.html
#include <QJsonArray>
#include <QTextStream>

Level::Level(const QString &name) : mName(name)
{
}

QString Level::name() const
{
    return mName;
}

QString Level::titleText() const
{
    return mTitleText;
}

QString Level::bodyText() const
{
    return mBodyText;
}

QList<Choice> Level::choices() const
{
    return mChoices;
}

QMessageBox::Icon Level::icon() const
{
    return mIcon;
}

//QMessageBox::StandardButtons Level::btnChoices()
//{
//    QList<QMessageBox::StandardButton>
//}

void Level::setChoices(const QList<Choice> &choices)
{
    mChoices = choices;
}

bool Level::getChoiceOfType(QMessageBox::StandardButton btnType, Choice &choice)
{
    if (!mChoices.isEmpty())
    {    for(int i =0; i < mChoices.length(); i++)
    {
        if (mChoices[i].button() == btnType)
        {
            choice =  mChoices[i];
            return true;
        }
    }}
    return false;
}

//! [0]
void Level::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("title") && json["title"].isString())
        mTitleText = json["title"].toString();

    if (json.contains("body") && json["body"].isString())
        mBodyText = json["body"].toString();

    if (json.contains("icon") && json["icon"].isDouble())
        mIcon = QMessageBox::Icon(json["icon"].toInt());
    else mIcon = QMessageBox::Information;

    if (json.contains("choices") && json["choices"].isArray()) {
        QJsonArray choiceArray = json["choices"].toArray();
        mChoices.clear();
        mChoices.reserve(choiceArray.size());
        for (const QJsonValue &v : choiceArray) {
            QJsonObject choiceObject = v.toObject();
            Choice choice;
            choice.read(choiceObject);
            mChoices.append(choice);
        }
    }
}
//! [0]

//! [1]
void Level::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["title"] = mTitleText;
    json["body"] = mBodyText;
    json["icon"] = mIcon;
    QJsonArray choiceArray;
    for (const Choice &choice : mChoices) {
        QJsonObject choiceObject;
        choice.write(choiceObject);
        choiceArray.append(choiceObject);
    }
    json["choices"] = choiceArray;
}
//! [1]

void Level::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Name:\t" << mName << "\n";

    QTextStream(stdout) << indent << "Title:\t" << mTitleText << "\n";

    QTextStream(stdout) << indent << "Body:\t" << mBodyText << "\n";

    QTextStream(stdout) << indent << "Choices:\n";
    for (const Choice &choice : mChoices)
        choice.print(2);
}
