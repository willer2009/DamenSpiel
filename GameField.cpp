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

    labelPlayer1 = new QLabel(" play: ");
    labelPlayer1->setFont(QFont("Commic Sans MS", 16, QFont::Bold, true));
    labelPlayer1->setTextFormat(Qt::RichText);
    labelPlayer1->setText("Play :  <img src= ':/images/greenTile.png'> ");

    QLabel *borderBottomLeftLabel = new QLabel;
    borderBottomLeftLabel->setPixmap(borderBottomLeft);
    QLabel *borderBottomRightLabel = new QLabel;
    borderBottomRightLabel->setPixmap(borderBottomRight);
    QLabel *borderTopLeftLabel = new QLabel;
    borderTopLeftLabel->setPixmap(borderTopLeft);
    QLabel *borderTopRightLabel = new QLabel;
    borderTopRightLabel->setPixmap(borderTopRight);

    gameFieldLayout = new QGridLayout;
    QColor blackColor = Qt::black;
    QColor whiteColor = Qt::white ;

    for (int i = 0; i < Data::NUMBER_ROWS; i++){
        for(int j = 0; j < Data::NUMBER_COLUMNS; j++){

            if ((i % 2 == 0 && j % 2 == 0) ||(i % 2 == 1 && j % 2 == 1)){
                fields[i][j] = new Field(blackColor, i, j);
            } else {
                fields[i][j] = new Field(whiteColor, i, j);
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
   // borderLayout->addWidget(labelPlayer2, 0, 1, 1, 10, Qt::AlignCenter);
    borderLayout->addWidget(borderTopRightLabel, 0, 11, 1, 1);

    borderLayout->addWidget(borderLeftLabel, 1, 0, 10, 1);
    borderLayout->addLayout(gameFieldLayout, 1, 1, 10, 10, Qt::AlignHCenter);
    borderLayout->addWidget(borderRightLabel, 1, 11, 10, 1);

    borderLayout->addWidget(borderBottomLeftLabel, 11, 0, 1, 1);
    borderLayout->addWidget(borderBottomLabel, 11, 1, 1, 10);
    borderLayout->addWidget(labelPlayer1, 11, 1, 1, 10, Qt::AlignCenter);
    borderLayout->addWidget(borderBottomRightLabel, 11, 11, 1, 1);

    borderLayout->setHorizontalSpacing(0);
    borderLayout->setVerticalSpacing(0);

//     QWidget *around = new QWidget();
//     QGridLayout *baseLayout = new QGridLayout;
//     baseLayout->setGeometry(QRect(0, 0, 250, 250));
//     QLabel border(around);
//     Q
//     QPixmap pixmap(":/images/cadre.jpg");
//     border.setPixmap(pixmap);
//     baseLayout->addWidget(border, 0, 0);
//     baseLayout->addWidget(gameFieldLayout);


    setLayout(borderLayout);

}

void GameField::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
         emit clicked();
    }
}



Field* GameField::getField(int i, int j){
    return this->fields[i][j];
}

QGridLayout* GameField::getGameFieldLayout(){
    return this->gameFieldLayout;
}


QLabel* GameField::getLabelPlayer1(){
    return labelPlayer1;
}

void GameField::setLabelPlayer1(QString text){
    this->labelPlayer1->setText(text);
}

GameField::~GameField(){

}
