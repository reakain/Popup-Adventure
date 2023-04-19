#ifndef PLAYER_H
#define PLAYER_H


#include <QJsonObject>
#include <QObject>
#include <QString>

/*
 * Our player character data. This currently does nothing lol
 */

//! [0]
class Player
{
    Q_GADGET

public:
    enum ClassType {
        Warrior, Mage, Archer
    };
    Q_ENUM(ClassType)

    Player();
    Player(const QString &name, int level, ClassType classType);

    QString name() const;
    void setName(const QString &name);

    int level() const;
    void setLevel(int level);

    ClassType classType() const;
    void setClassType(ClassType classType);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString mName;
    int mLevel = 0;
    ClassType mClassType = Warrior;
};
//! [0]

#endif // PLAYER_H
