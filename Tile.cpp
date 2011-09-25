#include "Tile.h"

Tile::Tile(QString type, int row, int column, QString playerName){
    this->type = type;
    this->row = row;
    this->column = column;
    this->playerName = playerName;
}

QString Tile::getType(){
    return this->type;
}

QString Tile::getPlayerName(){
    return this->playerName;
}

int Tile::getRow(){
    return this->row;
}

int Tile::getColumn(){
    return this->column;
}

void Tile::setRow(int newRow){
    this->row = newRow;
}

void Tile::setColumn(int newColumn){
    this->column = newColumn;
}

void Tile::setType(QString newType){
    this->type = newType;
}

void Tile::setPlayerName(QString newPlayerName){
    this->playerName = newPlayerName;
}

void Tile::mousePressEvent(QMouseEvent *ev){
    if (ev->button() == Qt::LeftButton){
        emit clicked();
    }
}
