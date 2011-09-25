#include "Player.h"
#include "Data.h"

Player::Player(QString name, QColor col, QString direction){
    this->name = name;
    this->color = col;
    this->direction = direction;
    QPixmap greenTile(":/images/greenTile.png");
    QImage greenTileImage = greenTile.toImage();
    QPixmap greenTile2 = QPixmap::fromImage(greenTileImage.scaled(Data::WIDTH_TILE, Data::HEIGTH_TILE, Qt::IgnoreAspectRatio, Qt::FastTransformation), Qt::AutoColor);

    QPixmap redTile(":/images/redTile2.png");
    QImage redTileImage = redTile.toImage();
    QPixmap redTile2 = QPixmap::fromImage(redTileImage.scaled(Data::WIDTH_TILE, Data::HEIGTH_TILE, Qt::IgnoreAspectRatio, Qt::FastTransformation), Qt::AutoColor);
    for (int i = 0; i < Data::NUMBER_TILES; i++){
        tiles[i] = new Tile("normal", -1, -1, this->name);
        if(this->color == Qt::green){
            tiles[i]->setPixmap(greenTile2);
        }else{
            tiles[i]->setPixmap(redTile2);
        }

    }
}

Player::Player(){

}

//Player::Player(Player p){
//    this->name = p.name;
//    this->color = p.color;
//    this->tiles = p.tiles;
//}

QString Player::getName(){
    return this->name;
}

QColor Player::getColor(){
    return color;
}
Tile* Player::getTile(int i){
     return this->tiles[i];

}

QString Player::getDirection(){
    return direction;
}

Player::~Player(){

}
