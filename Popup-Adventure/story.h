#ifndef STORY_H
#define STORY_H

#include "choice.h"
#include "level.h"

#include <QJsonObject>
#include <QList>
#include <QCborMap>
#include <QCborValue>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>

/*
 * All our story data
 */

class Story
{
public:
    //Story() = default;
    //explicit Story(QString fileName = "story.json");

    QList<Level> levels() const;
    void setLevels(const QList<Level> &levels);

    bool getLevelWithName(QString lvlName, Level &level);

    bool loadStory(QString fileName = "story.json");

    // Reading from json
    void read(const QJsonObject &json);
    //void write(QJsonObject &json) const;

private:
    QList<Level> mLevels;
};

#endif // STORY_H
