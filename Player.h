#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"

/**
  * class which represents a player in the game
  */

class Player{
private:
    //number of the adverse tile which has been removed
    int adverseRemovedTile;

    // name of the player
    QString name;

    //color of the tiles of the player
    QString color;

    //array which contains the tiles of the player
    Tile *tiles[20];

    //direction which a normal tile of the player has to take( from the bottom to the top or the other direction)
    QString direction;

public:
    Player();
    // create a new player
    Player(QString name, QString color, QString direction);

    //return the name of the player
    QString getName() const;

    //returns the color of the tiles of the player
    QString getColor() const;

    //return the reference on the tile number i in the array of tiles of the player
    Tile* getTile(int i) const;

    //returns the direction, which a normal tile of the player has to take
    QString getDirection() const;

    //returns the number of adverse tiles which the player has removed
    int getAdverseRemovedTile() const;

    //increment the number of adverse tiles which the player has removed
    void addAdverseRemovedTile();

    //compare to player object and returns true if the attributs of the two player contains the same values
    bool operator ==(Player const& player);

    //destroy a player
    ~Player();
};

#endif // PLAYER_H
