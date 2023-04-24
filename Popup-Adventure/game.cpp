#include "game.h"

#include <QCborMap>
#include <QCborValue>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>


Player Game::player() const
{
    return mPlayer;
}

QList<Level> Game::levels() const
{
    return mLevels;
}

Level Game::currentLevel() const
{
    return mCurrentLevel;
}

QList<StorySave> Game::storySaves() const
{
    return mStorySaves;
}

void Game::updateSave(QString storyName, QString currentLevelName)
{
    int index = 0;
    if(getSaveIndex(index, storyName))
    {
        mStorySaves[index].updateLevel(currentLevelName);
    }
    else
    {
        StorySave newSave(storyName, currentLevelName);
        mStorySaves.append(newSave);
    }

}

void Game::updateSave(StorySave newSaveData)
{
    updateSave(newSaveData.storyName(),newSaveData.currentLevel());
}

bool Game::getSaveIndex(int &index, QString storyName)
{
    if (!mStorySaves.isEmpty())
    {    for(int i =0; i < mStorySaves.length(); i++)
    {
        if (mStorySaves[i].storyName() == storyName)
        {
            index = i;
            return true;
        }
    }}
    return false;
}

//Return true if a save exists, false if it doesn't
bool Game::getGameSave(StorySave &storyData, QString storyName)
{
    if (!mStorySaves.isEmpty())
    {    for(int i =0; i < mStorySaves.length(); i++)
    {
        if (mStorySaves[i].storyName() == storyName)
        {
            storyData =  mStorySaves[i];
            return true;
        }
    }}
    return false;
}

void Game::setLevel(Level current)
{
    mCurrentLevel = current;
}

//! [0]
void Game::newGame()
{
    /*
    mPlayer = Player();
    mPlayer.setName(QStringLiteral("Hero"));
    mPlayer.setClassType(Player::Archer);
    mPlayer.setLevel(QRandomGenerator::global()->bounded(15, 21));
    */

    //mLevels.clear();
    //mLevels.reserve(2);
/*
    Level village(QStringLiteral("Village"));
    QList<Character> villageNpcs;
    villageNpcs.reserve(2);
    villageNpcs.append(Character(QStringLiteral("Barry the Blacksmith"),
                                 QRandomGenerator::global()->bounded(8, 11),
                                 Character::Warrior));
    villageNpcs.append(Character(QStringLiteral("Terry the Trader"),
                                 QRandomGenerator::global()->bounded(6, 8),
                                 Character::Warrior));
    village.setNpcs(villageNpcs);
    mLevels.append(village);

    Level dungeon(QStringLiteral("Dungeon"));
    QList<Character> dungeonNpcs;
    dungeonNpcs.reserve(3);
    dungeonNpcs.append(Character(QStringLiteral("Eric the Evil"),
                                 QRandomGenerator::global()->bounded(18, 26),
                                 Character::Mage));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Left Minion"),
                                 QRandomGenerator::global()->bounded(5, 7),
                                 Character::Warrior));
    dungeonNpcs.append(Character(QStringLiteral("Eric's Right Minion"),
                                 QRandomGenerator::global()->bounded(4, 9),
                                 Character::Warrior));
    dungeon.setNpcs(dungeonNpcs);
    mLevels.append(dungeon);
    */
}
//! [0]

//! [3]
bool Game::loadGame(Game::SaveFormat saveFormat)
{
    QFile loadFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData)
        : QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject()));

    read(loadDoc.object());

    QTextStream(stdout) << "Loaded save for "
                        << loadDoc["player"]["name"].toString()
                        << " using "
                        << (saveFormat != Json ? "CBOR" : "JSON") << "...\n";
    return true;
}
//! [3]

//! [4]
bool Game::saveGame(Game::SaveFormat saveFormat) const
{
    QFile saveFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    saveFile.write(saveFormat == Json
        ? QJsonDocument(gameObject).toJson()
        : QCborValue::fromJsonValue(gameObject).toCbor());

    return true;
}
//! [4]

//! [1]
void Game::read(const QJsonObject &json)
{
    /*
    if (json.contains("player") && json["player"].isObject())
        mPlayer.read(json["player"].toObject());

    if (json.contains("current_level") && json["current_level"].isObject())
        mCurrentLevel.read(json["current_level"].toObject());
        */


    if (json.contains("stories") && json["stories"].isArray()) {
        QJsonArray storyArray = json["stories"].toArray();
        mStorySaves.clear();
        mStorySaves.reserve(storyArray.size());
        for (const QJsonValue &v : storyArray) {
            QJsonObject storyObject = v.toObject();
            StorySave saveData;
            saveData.read(storyObject);
            mStorySaves.append(saveData);
        }
    }

}
//! [1]

//! [2]
void Game::write(QJsonObject &json) const
{
    /*
    QJsonObject playerObject;
    mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonObject currentLevelObject;
    mCurrentLevel.write(currentLevelObject);
    json["current_level"] = currentLevelObject;
    */


    QJsonArray storyArray;
    for (const StorySave &storySave : mStorySaves) {
        QJsonObject storyObject;
        storySave.write(storyObject);
        storyArray.append(storyObject);
    }
    json["stories"] = storyArray;

}
//! [2]

void Game::print(int indentation) const
{
    /*
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Player\n";
    mPlayer.print(indentation + 1);

    QTextStream(stdout) << indent << "Current Level\n";
    mCurrentLevel.print(indentation + 1);
    */

    //QTextStream(stdout) << indent << "Levels\n";
    //for (const Level &level : mLevels)
    //    level.print(indentation + 1);
}
