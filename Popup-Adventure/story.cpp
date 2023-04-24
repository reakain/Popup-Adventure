#include "story.h"

QString Story::title() const
{
    return mTitle;
}

QList<Level> Story::levels() const
{
    return mLevels;
}

void Story::setLevels(const QList<Level> &levels)
{
    mLevels = levels;
}

bool Story::getLevelWithName(QString lvlName, Level &level)
{
    if (!mLevels.isEmpty())
    {    for(int i =0; i < mLevels.length(); i++)
    {
        if (mLevels[i].name() == lvlName)
        {
            level =  mLevels[i];
            return true;
        }
    }}
    return false;
}

bool Story::loadStory(QString fileName)
{
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open story file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    QTextStream(stdout) << "Loaded save for "
                        << loadDoc["player"]["name"].toString()
                        << " using "
                        << ( "JSON") << "...\n";
    return true;
}

// Reading from json
void Story::read(const QJsonObject &json)
{
    if (json.contains("title") && json["title"].isString()) {
        mTitle = json["title"].toString();
    }
    if (json.contains("levels") && json["levels"].isArray()) {
        QJsonArray levelArray = json["levels"].toArray();
        mLevels.clear();
        mLevels.reserve(levelArray.size());
        for (const QJsonValue &v : levelArray) {
            QJsonObject levelObject = v.toObject();
            Level level;
            level.read(levelObject);
            mLevels.append(level);
        }
    }
}

