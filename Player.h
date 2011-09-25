#ifndef PLAYER_H
#define PLAYER_H

#include<QString>
#include<QColor>
#include <QImage>
#include "Tile.h"

class Player{
public:
    Player();
    Player(QString name, QColor color, QString direction);
    QString getName();
    QColor getColor();
    Tile* getTile(int i);
    QString getDirection();
     ~Player();

private:
    QString name;

    QColor color;

    Tile *tiles[20];

    QString direction;
};

#endif // PLAYER_H
