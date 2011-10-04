#ifndef FIELD_H
#define FIELD_H

#include <QLabel>
#include <QMouseEvent>

#include "tile.h"

class Field : public QLabel
{
    Q_OBJECT
public:
    Field(QColor color, int row, int column);

    void mousePressEvent(QMouseEvent *ev);
    bool getIsClicked();
    int getRow();
    int getColumn();
    bool getIsFree();
    QColor getInternColor();
    void setTile(Tile* tile);
    void setFree(bool b);
    Tile* getTile() const;

signals:
    void clicked();

public slots:
    //void selectMe();
    void renewBlackColor();


private:
    QColor internColor;
    int row;
    int column;
    bool isFree;
    //bool isClicked;
    Tile* tile;
};

#endif // FIELD_H
