#include "player.h"

#include <QMetaEnum>
#include <QTextStream>

Player::Player()
    = default;

Player::Player(const QString &name,
                     int level,
                     Player::ClassType classType) :
    mName(name),
    mLevel(level),
    mClassType(classType)
{
}

QString Player::name() const
{
    return mName;
}

void Player::setName(const QString &name)
{
    mName = name;
}

int Player::level() const
{
    return mLevel;
}

void Player::setLevel(int level)
{
    mLevel = level;
}

Player::ClassType Player::classType() const
{
    return mClassType;
}

void Player::setClassType(Player::ClassType classType)
{
    mClassType = classType;
}

//! [0]
void Player::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("level") && json["level"].isDouble())
        mLevel = json["level"].toInt();

    if (json.contains("classType") && json["classType"].isDouble())
        mClassType = ClassType(json["classType"].toInt());
}
//! [0]

//! [1]
void Player::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["level"] = mLevel;
    json["classType"] = mClassType;
}
//! [1]

void Player::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Name:\t" << mName << "\n";
    QTextStream(stdout) << indent << "Level:\t" << mLevel << "\n";

    QString className = QMetaEnum::fromType<ClassType>().valueToKey(mClassType);
    QTextStream(stdout) << indent << "Class:\t" << className << "\n";
}
