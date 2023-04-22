#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "choice.h"
#include "level.h"

#include <QJsonObject>
#include <QList>

/*
 * Our game data class. Currently doesn't do a whole lot
 */

class Game
{
public:
    enum SaveFormat {
        Json, Binary
    };

    Player player() const;
    QList<Level> levels() const;
    Level currentLevel() const;

    void setLevel(Level current);

    void newGame();
    bool loadGame(SaveFormat saveFormat);
    bool saveGame(SaveFormat saveFormat) const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    Player mPlayer;
    Level mCurrentLevel;
    QList<Level> mLevels;
};

#endif // GAME_H
