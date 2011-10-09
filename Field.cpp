#include "Field.h"
#include "Data.h"
#include <QPixmap>
#include <QPainter>

Field::Field(QString color, int row, int column) :
    QLabel()
{
    this->setFixedSize(Data::WIDTH_FIELD, Data::HEIGTH_FIELD);
    internColor = color;
    this->row = row;
    this->column = column;
    isFree = true;
    //isClicked = false;
    tile = 0;
    if (internColor == "black"){
        QPixmap blackPixmap(":/images/black.bmp");
        this->setPixmap(blackPixmap);
    } else if (internColor == "white"){
        QPixmap whitePixmap(":/images/white.bmp");
        this->setPixmap(whitePixmap);
    }

    //connect(this, SIGNAL(clicked()), this , SLOT(changePixmap()));

}

void Field::mousePressEvent(QMouseEvent *ev){
    if (ev->button() == Qt::LeftButton){
        emit clicked();
    }
}

/*void Field::selectMe(){
    if(internColor == Qt::black){
        this->isClicked = true;
    }
}*/

void Field::renewBlackColor(){
    QPixmap blackPixmap(":/images/black.bmp");
    this->setPixmap(blackPixmap);
}

bool Field::getIsFree(){
    return this->isFree;
}
/*bool Field::getIsClicked(){
    return isClicked;
}*/
int Field::getRow(){
    return row;
}

int Field::getColumn(){
    return column;
}

QString Field::getInternColor(){
    return internColor;
}
void Field::setTile(Tile* newTile){
    this->tile = newTile;
}
void Field::setFree(bool b){
    this->isFree = b;
}

Tile* Field::getTile() const{
    return tile;
}

Field::~Field(){

}
