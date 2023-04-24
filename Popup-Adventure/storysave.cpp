#include "storysave.h"

StorySave::StorySave(const QString &storyName, const QString &currentLevelName) : mStoryName(storyName), mCurrentLevel(currentLevelName)
{
}

QString StorySave::storyName() const
{
    return mStoryName;
}

QString StorySave::currentLevel() const
{
    return mCurrentLevel;
}

void StorySave::updateLevel(const QString currentLevelName)
{
    mCurrentLevel = currentLevelName;
}


void StorySave::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mStoryName = json["name"].toString();

    if (json.contains("current_level") && json["current_level"].isString())
        mCurrentLevel = json["current_level"].toString();
}

void StorySave::write(QJsonObject &json) const
{
    json["name"] = mStoryName;
    json["current_level"] = mCurrentLevel;
}
