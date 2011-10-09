#include "Tile.h"

Tile::Tile(QString type, int row, int column, QString playerName){
    this->type = type;
    this->row = row;
    this->column = column;
    this->playerName = playerName;
}

QString Tile::getType() const{
    return this->type;
}

QString Tile::getPlayerName() const{
    return this->playerName;
}

int Tile::getRow() const{
    return this->row;
}

int Tile::getColumn() const{
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

bool Tile::operator ==(Tile const& tile1){
    return tile1.row == row && tile1.column == this->column && tile1.playerName == this->playerName && tile1.type == this->type;
}

Tile::~Tile(){
}
