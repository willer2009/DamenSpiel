#ifndef TILE_H
#define TILE_H

#include<QtGui>

/**
  * class which represents a tile in the game
  */

class Tile : public QLabel{
    Q_OBJECT


private:
    //type of the tile(normal or king)
    QString type;

    // row where the tile is located
    int row;

    //column where the tile ist located
    int column;

    //name of the player who ows the tile
    QString playerName;

public:
    //create a new tile
    Tile(QString type, int row, int Column, QString playerName);

    //returns the type of the tile
    QString getType() const;

    //returns the name of the player who ows the tile
    QString getPlayerName() const;

    //returns the row where the tile is located
    int getRow() const;

    //returns the column where the tile is located
    int getColumn() const;

    // change the type of a tile with the give type as parameter
    void setType(QString newType);

    //change the row of the tile with the given value in parameter
    void setRow(int newRow);

    //change the column of the tile with the given value in parameter
    void setColumn(int newColumn);

    //change the name of the player who ows the tile
    void setPlayerName(QString newPlayerName);

    //this function is called when the mouse is pressed on the tile
    void mousePressEvent(QMouseEvent *ev);

    //compare two tile and returns true when their attributes contains the same value and false if not
    bool operator ==(Tile const& tile1);

    //destroy the tile
    virtual ~Tile();


signals:
    //this signal is emitted when the the mouse is pressed on the tile
    void clicked();

public slots:
    //void selectMe();



};

#endif // TILE_H
