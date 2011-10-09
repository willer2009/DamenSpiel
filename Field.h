#ifndef FIELD_H
#define FIELD_H

#include <QLabel>
#include <QMouseEvent>

#include "tile.h"

class Field : public QLabel
{
    Q_OBJECT
private:
    // color of a unique field in z´the game area
    QString internColor;

    //row's postion of a field in the game area
    int row;

    //column's postion of a field in the game area
    int column;

    // show if a field contains a tile or not is free or not
    bool isFree;

    // tile which the field contains
    Tile* tile;

public:
    /**
      * create a new field in the game area
      */
    Field(QString color, int row, int column);
    //that function is called when the mouse is pressed on a field
    void mousePressEvent(QMouseEvent *ev);

    //bool getIsClicked();
    //return the row where the field is situated
    int getRow();

    //return the column where the field is situated
    int getColumn();

    //return true if the field is free and false else
    bool getIsFree();

    // return the color of the field
    QString getInternColor();

    //change the tile of a field with the given tile as parameter
    void setTile(Tile* tile);

    //change the state of the field to free(true) or occupied(false)
    void setFree(bool b);

    //return the reference to the tile which is in the actuel field
    Tile* getTile() const;

    //destroy the field
    virtual ~Field();

signals:
    //this signal is emitted when the field is clicked
    void clicked();

public slots:
    void renewBlackColor();



};

#endif // FIELD_H
