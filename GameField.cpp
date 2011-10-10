#include "GameField.h"
#include "Data.h"

GameField::GameField(): QWidget()
{


    //this->setFixedSize(500, 500);


    borderLayout = new QGridLayout;

    QPixmap borderTop(":/images/borderTop.JPG");
    QPixmap borderBottom(":/images/borderBottom.JPG");
    QPixmap borderLeft(":/images/borderLeft.JPG");
    QPixmap borderRight(":/images/borderRight.JPG");
    QPixmap borderTopLeft(":/images/borderTopLeft.JPG");
    QPixmap borderTopRight(":/images/borderTopRight.JPG");
    QPixmap borderBottomLeft(":/images/borderBottomLeft.JPG");
    QPixmap borderBottomRight(":/images/borderBottomRight.JPG");

    QLabel *borderBottomLabel = new QLabel;
    borderBottomLabel->setPixmap(borderBottom);
    QLabel *borderTopLabel = new QLabel;
    borderTopLabel->setPixmap(borderTop);
    QLabel *borderRightLabel = new QLabel;
    borderRightLabel->setPixmap(borderRight);
    QLabel *borderLeftLabel = new QLabel;
    borderLeftLabel->setPixmap(borderLeft);

    labelActuelPlayer = new QLabel(" ");
    labelActuelPlayer->setFont(QFont("Commic Sans MS", 16, QFont::Bold, true));
    labelActuelPlayer->setTextFormat(Qt::RichText);
    labelActuelPlayer->setText("Play :  <img src= ':/images/greenTile.png'> ");

    removedTilePlayer1 = new QLabel(" ");
    removedTilePlayer1->setFont(QFont("Commic Sans MS", 16, QFont::Bold, true));
    removedTilePlayer1->setTextFormat(Qt::RichText);
    removedTilePlayer1->setText(" <img src= ':/images/redTile2.png'> : 00 ");

    removedTilePlayer2 = new QLabel(" ");
    removedTilePlayer2->setFont(QFont("Commic Sans MS", 16, QFont::Bold, true));
    removedTilePlayer2->setTextFormat(Qt::RichText);
    removedTilePlayer2->setText("<img src= ':/images/greenTile.png'> : 00 ");

    QLabel *borderBottomLeftLabel = new QLabel;
    borderBottomLeftLabel->setPixmap(borderBottomLeft);
    QLabel *borderBottomRightLabel = new QLabel;
    borderBottomRightLabel->setPixmap(borderBottomRight);
    QLabel *borderTopLeftLabel = new QLabel;
    borderTopLeftLabel->setPixmap(borderTopLeft);
    QLabel *borderTopRightLabel = new QLabel;
    borderTopRightLabel->setPixmap(borderTopRight);

    gameFieldLayout = new QGridLayout;

    for (int i = 0; i < Data::NUMBER_ROWS; i++){
        for(int j = 0; j < Data::NUMBER_COLUMNS; j++){

            if ((i % 2 == 0 && j % 2 == 0) ||(i % 2 == 1 && j % 2 == 1)){
                fields[i][j] = new Field("black", i, j);
            } else {
                fields[i][j] = new Field("white", i, j);
            }
           gameFieldLayout->addWidget(fields[i][j], i, j);

            /*QObject::connect(fields[i][j], SIGNAL(clicked()), fields[i][j], SLOT(selectMe()));
            QObject::connect(fields[i][j], SIGNAL(clicked()), this, SLOT(selectPossibleNeighbors()));*/

       }
    }
    gameFieldLayout->setHorizontalSpacing(0);
    gameFieldLayout->setVerticalSpacing(0);

    borderLayout->addWidget(borderTopLeftLabel, 0, 0, 1, 1);
    borderLayout->addWidget(borderTopLabel, 0, 1, 1, 10);
    borderLayout->addWidget(borderTopRightLabel, 0, 11, 1, 1);

    borderLayout->addWidget(borderLeftLabel, 1, 0, 10, 1);
    borderLayout->addLayout(gameFieldLayout, 1, 1, 10, 10, Qt::AlignHCenter);
    borderLayout->addWidget(borderRightLabel, 1, 11, 10, 1);

    borderLayout->addWidget(removedTilePlayer1, 0, 1, 1, 10, Qt::AlignLeft);
    borderLayout->addWidget(removedTilePlayer2, 0, 1, 1, 10, Qt::AlignRight);


    borderLayout->addWidget(borderBottomLeftLabel, 11, 0, 1, 1);
    borderLayout->addWidget(borderBottomLabel, 11, 1, 1, 10);
    borderLayout->addWidget(labelActuelPlayer, 11, 1, 1, 10, Qt::AlignCenter);
    borderLayout->addWidget(borderBottomRightLabel, 11, 11, 1, 1);

    borderLayout->setHorizontalSpacing(0);
    borderLayout->setVerticalSpacing(0);

    setLayout(borderLayout);

}

/*void GameField::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
         emit clicked();
    }
}/*/



Field* GameField::getField(int i, int j){
    return this->fields[i][j];
}

QGridLayout* GameField::getGameFieldLayout(){
    return this->gameFieldLayout;
}


QLabel* GameField::getLabelActuelPlayer(){
    return labelActuelPlayer;
}

QLabel * GameField::getLabelRemovedTilePlayer1(){
    return this->removedTilePlayer1;
}

QLabel * GameField::getLabelRemovedTilePlayer2(){
    return this->removedTilePlayer2;
}

void GameField::setLabelActuelPlayer(QString text){
    this->labelActuelPlayer->setText(text);
}


GameField::~GameField(){
/**
  All the pointer in this class are positionned on a Layout which will be recursivly destroyed,
  when the Qwidget(parent) will be destroy, so we don't need to do anything.
  */
}
