#include "Player.h"
#include "Data.h"

Player::Player(QString name, QString col, QString direction){
    this->name = name;
    this->color = col;
    this->direction = direction;
    adverseRemovedTile = 0;
    QPixmap greenTile(":/images/greenTile.png");
    QImage greenTileImage = greenTile.toImage();
    QPixmap greenTile2 = QPixmap::fromImage(greenTileImage.scaled(Data::WIDTH_TILE, Data::HEIGTH_TILE, Qt::IgnoreAspectRatio, Qt::FastTransformation), Qt::AutoColor);

    QPixmap redTile(":/images/redTile2.png");
    QImage redTileImage = redTile.toImage();
    QPixmap redTile2 = QPixmap::fromImage(redTileImage.scaled(Data::WIDTH_TILE, Data::HEIGTH_TILE, Qt::IgnoreAspectRatio, Qt::FastTransformation), Qt::AutoColor);
    for (int i = 0; i < Data::NUMBER_TILES; i++){
        tiles[i] = new Tile("normal", -1, -1, this->name);
        if(this->color == "green"){
            tiles[i]->setPixmap(greenTile2);
        }else{
            tiles[i]->setPixmap(redTile2);
        }

    }
}


Player::Player(){

}

QString Player::getName() const{
    return this->name;
}

QString Player::getColor()const{
    return color;
}
Tile* Player::getTile(int i) const{
     return this->tiles[i];

}

QString Player::getDirection() const{
    return direction;
}

int Player::getAdverseRemovedTile() const{
    return adverseRemovedTile;
}

void Player::addAdverseRemovedTile() {
    adverseRemovedTile++;
}

Player::~Player(){

}

bool Player::operator ==(Player const& player){
    return player.name == this->name;
}
