#ifndef STORYSAVE_H
#define STORYSAVE_H

#include <QJsonObject>
#include <QList>

class StorySave
{
public:
    StorySave() = default;
    explicit StorySave(const QString &storyName, const QString &currentLevelName);

    QString storyName() const;
    QString currentLevel() const;

    void updateLevel(const QString currentLevelName);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString mStoryName;
    QString mCurrentLevel;
};

#endif // STORYSAVE_H
