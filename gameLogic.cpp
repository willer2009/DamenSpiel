#include "gameLogic.h"
#include "Data.h"

GameLogic::GameLogic(Player *p1, Player *p2, GameField *gameField, MainWindow *mainWindow) : QObject(){
    this->player1 = p1;
    this->player2 = p2;
    this->gameField = gameField;
    this->mainWindow = mainWindow;
    connect(this->mainWindow, SIGNAL(restartGame()), this, SLOT(restart()));
    connect(this->mainWindow->getSettingsDialog(), SIGNAL(accepted()), this, SLOT(hideOrShowCurrentPlayer()));
    connect(this->mainWindow->getSettingsDialog(), SIGNAL(rejected()), this, SLOT(checkDialogState()));
    mainWindow->setCentralWidget(gameField);
    actuelPlayer = this->chooseFirstPlayer();
    isTileSelected = false;
    //somethingHasChanged = false;
    selectedTile = 0;
    destinationField = 0;
}

void GameLogic::start(){
    int n1 = 0;
    int n2 = 0;
    for (int i = 0; i < Data::NUMBER_ROWS - 6;i++){
        for(int j = 0; j < Data::NUMBER_COLUMNS;j++){
            //the first 4 rows of tiles
            if(this->gameField->getField(i, j)->getInternColor() == Qt::black && n1 < Data::NUMBER_TILES){
                this->gameField->getField(i, j)->setTile(player2->getTile(n1));
                this->gameField->getField(i, j)->setFree(false);
                player2->getTile(n1)->setRow(i);
                player2->getTile(n1)->setColumn(j);
                gameField->getGameFieldLayout()->addWidget(player2->getTile(n1), i, j, Qt::AlignHCenter);
                QObject::connect(player2->getTile(n1), SIGNAL(clicked()), this, SLOT(selectTile()));
                QObject::connect(player2->getTile(n1), SIGNAL(clicked()), this, SLOT(selectPossibleNeighborsWhereToPlay()));
                player2->getTile(n1)->move(5, 5);
                n1++;
            }
            //the last 4 rows of tiles
            if(this->gameField->getField(i + 6, j)->getInternColor() == Qt::black && n2 < Data::NUMBER_TILES){
                this->gameField->getField(i + 6, j)->setTile(player1->getTile(n2));
                this->gameField->getField(i + 6, j)->setFree(false);
                player1->getTile(n2)->setRow(i + 6);
                player1->getTile(n2)->setColumn(j);
                gameField->getGameFieldLayout()->addWidget(player1->getTile(n2), i + 6, j, Qt::AlignHCenter);
                QObject::connect(player1->getTile(n2), SIGNAL(clicked()), this, SLOT(selectTile()));
                QObject::connect(player1->getTile(n2), SIGNAL(clicked()), this, SLOT(selectPossibleNeighborsWhereToPlay()));
                player1->getTile(n2)->move(5, 5);
                n2++;
            }
        }
    }
    //the fields have to be able to return a signal when thy will be clicked
    for (int i = 0; i < Data::NUMBER_ROWS;i++){
        for(int j = 0; j < Data::NUMBER_COLUMNS;j++){
            QObject::connect(this->gameField->getField(i, j), SIGNAL(clicked()), this, SLOT(move()));
        }
    }
}


void GameLogic::restart(){

    delete this->player1;
    delete this->player2;
    delete this->gameField;

    this->gameField = new GameField;
    this->player1 = new Player("player1", Qt::green, "toTheTop");
    this->player2 = new Player("player2", Qt::gray, "toTheBottom");
    this->mainWindow->setCentralWidget(gameField);
    actuelPlayer = this->chooseFirstPlayer();
    isTileSelected = false;
    //somethingHasChanged = false;
    selectedTile = 0;
    destinationField = 0;
    this->start();
}

void GameLogic::selectTile(){
    this->selectedTile = qobject_cast<Tile*>(sender());
    //this->playSelectedSound();
    //this->isTileSelected = true;
}

void GameLogic::selectDest(){
    Field * field = qobject_cast<Field*>(sender());
    if(field->getIsFree()){
        this->destinationField = qobject_cast<Field*>(sender());
    }
}

QString GameLogic::getNormalDirection(Tile *tile){

    QString direction;

    if(player1->getName() == tile->getPlayerName()){
        direction = player1->getDirection();
    }else{
        direction = player2->getDirection();
    }

    if (direction == "toTheTop"){
        return "toTheTop";
    }else if(direction == "toTheBottom"){
        return "toTheBottom";
    }else{
        return "allDirection";
    }
}


bool GameLogic::isAdverseTile(int i, int j){
    if(actuelPlayer->getName() == "player1"){
        for(int n = 0; n < Data::NUMBER_TILES; n++){
            if (player2->getTile(n)->getColumn() == j && player2->getTile(n)->getRow() == i){
                return true;
            }
        }
    }else if(actuelPlayer->getName() == "player2"){
        for(int n = 0; n < Data::NUMBER_TILES; n++){
            if (player1->getTile(n)->getColumn() == j && player1->getTile(n)->getRow() == i){
                return true;
            }
        }
    }
    return false;
}

Player* GameLogic::chooseFirstPlayer(){
    return player1;
}


bool GameLogic::canTakeTile(){
    if(selectedTile != 0){
        int selectedRow = selectedTile->getRow();
        int selectedColumn = selectedTile->getColumn();

        if(selectedRow + 1 < Data::NUMBER_ROWS && selectedColumn + 1 < Data::NUMBER_COLUMNS){
            if(!this->gameField->getField(selectedRow + 1, selectedColumn + 1)->getIsFree()
                 && isAdverseTile(selectedRow + 1, selectedColumn + 1)){
                if((selectedRow + 2 < Data::NUMBER_ROWS && selectedColumn + 2 < Data::NUMBER_COLUMNS)
                    && this->gameField->getField(selectedRow + 2, selectedColumn + 2)->getIsFree()){
                    return true;
                }
            }
        }
        if(selectedRow + 1 < Data::NUMBER_ROWS && selectedColumn - 1 >= 0){
            if(!this->gameField->getField(selectedRow + 1, selectedColumn - 1)->getIsFree()
               && isAdverseTile(selectedRow + 1, selectedColumn - 1)){
                if((selectedRow + 2 < Data::NUMBER_ROWS && selectedColumn - 2 >= 0)
                    && this->gameField->getField(selectedRow + 2, selectedColumn - 2)->getIsFree()){
                    return true;
                }
            }
        }
        if(selectedRow - 1 >= 0 && selectedColumn - 1 >= 0){
            if(!this->gameField->getField(selectedRow - 1, selectedColumn - 1)->getIsFree()
               && isAdverseTile(selectedRow - 1, selectedColumn - 1)){
                if((selectedRow - 2 >= 0 && selectedColumn - 2 >= 0)
                    && this->gameField->getField(selectedRow - 2, selectedColumn - 2)->getIsFree()){
                    return true;
                }
            }
        }
        if(selectedRow - 1 >= 0 && selectedColumn + 1 < Data::NUMBER_COLUMNS){
            if(!this->gameField->getField(selectedRow - 1, selectedColumn + 1)->getIsFree()
               && isAdverseTile(selectedRow - 1, selectedColumn + 1)){
                if((selectedRow - 2 >= 0 && selectedColumn + 2 < Data::NUMBER_COLUMNS)
                    && this->gameField->getField(selectedRow - 2, selectedColumn + 2)->getIsFree()){
                    return true;
                }
            }
        }
        return false;
    }else{
        return false;
    }
}

/*bool canTakeTileAt(int relativeRow, int relativeColumn){
    if(selectedRow  >= 0 && selectedColumn + 1 < Data::NUMBER_COLUMNS){
        if(!this->gameField->getField(selectedRow - 1, selectedColumn + 1)->getIsFree()
           && isAdverseTile(selectedRow - 1, selectedColumn + 1)){
            if((selectedRow - 2 >= 0 && selectedColumn + 2 < Data::NUMBER_COLUMNS)
                && this->gameField->getField(selectedRow - 2, selectedColumn + 2)->getIsFree()){
                return true;
            }
        }
    }
}*/

void GameLogic::changeActuelPlayer(){
    if(actuelPlayer->getName() == "player1"){
        this->gameField->getLabelPlayer1()->setText("Play :  <img src= ':/images/redTile2.png'> ");
        actuelPlayer = this->player2;
    }else if(actuelPlayer->getName() == "player2"){
        this->gameField->getLabelPlayer1()->setText("Play :  <img src= ':/images/greenTile.png'> ");
        actuelPlayer = this->player1;
    }
}

bool GameLogic::isTileOfActuelPlayer(Tile *tile){
    return tile->getPlayerName() == actuelPlayer->getName();
}

void GameLogic::hideOrShowCurrentPlayer(){
    if(this->mainWindow->getSettingsDialog()->getStatus()){
        this->gameField->getLabelPlayer1()->show();
    }else{
        this->gameField->getLabelPlayer1()->hide();
    }
}


void GameLogic::playSelectedSound(){
    QSound sound("C:/Users/sylvain/Documents/QtProjekt/DamenSpiel4/sounds/click.wav");
    sound.play();
}
void GameLogic::playMoveSound(){
    QSound sound("C:/Users/sylvain/Documents/QtProjekt/DamenSpiel4/sounds/move.wav");
    sound.play();
}
void GameLogic::error(){
    QSound sound("C:/Users/sylvain/Documents/QtProjekt/DamenSpiel4/sounds/mov.wav");
    sound.play();
}

void GameLogic::checkDialogState(){
    if(this->gameField->getLabelPlayer1()->isVisible() && !this->mainWindow->getSettingsDialog()->getStatus()){
        this->mainWindow->getSettingsDialog()->check();
    }
    if(!this->gameField->getLabelPlayer1()->isVisible() && this->mainWindow->getSettingsDialog()->getStatus()){
        this->mainWindow->getSettingsDialog()->uncheck();
    }
}

bool GameLogic::isPossibleToMove(){
    if (destinationField != 0 && selectedTile != 0 && this->getNormalDirection(selectedTile) == "toTheTop"){
        return (destinationField->getIsFree()
                && abs(destinationField->getColumn() - selectedTile->getColumn()) == 1
                && (destinationField->getRow() - selectedTile->getRow()) == -1);
    }else if(destinationField != 0 && selectedTile != 0 && this->getNormalDirection(selectedTile) == "toTheBottom"){
        return (destinationField->getIsFree()
                && abs(destinationField->getColumn() - selectedTile->getColumn()) == 1
                && (destinationField->getRow() - selectedTile->getRow()) == 1);
    }else if(destinationField != 0 && selectedTile != 0 && this->getNormalDirection(selectedTile) == "allDirection"){
        return (destinationField->getIsFree()
                && abs(destinationField->getColumn() - selectedTile->getColumn()) == 1
                && abs(destinationField->getRow() - selectedTile->getRow()) == 1);
    }else{
         return false;
        }
}


void GameLogic::selectPossibleNeighborsWhereToPlay(){
    QPixmap orangePixmap(":/images/orange.bmp");
    //Tile *selectedTile = qobject_cast<Tile*>(sender());
    int myRow = selectedTile->getRow();
    int myColumn = selectedTile->getColumn();

    if(!canTakeTile()){
        //select the direct neighbors: it is only a move
        if(isTileOfActuelPlayer(selectedTile) && (this->getNormalDirection(selectedTile) == "toTheBottom"
                                                  || this->getNormalDirection(selectedTile) == "allDirection")){
             if(myRow + 1 < Data::NUMBER_ROWS){
                   if (myColumn - 1 >= 0){
                        if( this->gameField->getField(myRow + 1, myColumn - 1)->getIsFree()){
                             this->gameField->getField(myRow + 1, myColumn - 1)->setPixmap(orangePixmap);
                             QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, this->gameField->getField(myRow + 1, myColumn - 1),
                                                SLOT(renewBlackColor()));
                            }
                        }
                   if(myColumn + 1 < Data::NUMBER_COLUMNS){
                        if(this->gameField->getField(myRow + 1, myColumn + 1)->getIsFree()){
                             this->gameField->getField(myRow + 1, myColumn + 1)->setPixmap(orangePixmap);
                             QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, this->gameField->getField(myRow + 1, myColumn + 1),
                                                SLOT(renewBlackColor()));
                         }
                    }
              }
       }else if(isTileOfActuelPlayer(selectedTile) && (this->getNormalDirection(selectedTile) == "toTheTop"
                                                       || this->getNormalDirection(selectedTile) == "allDirection")){
             if(myRow - 1 >= 0){
                  if(myColumn - 1 >= 0){
                       if(this->gameField->getField(myRow - 1, myColumn - 1)->getIsFree()){
                           this->gameField->getField(myRow - 1, myColumn - 1)->setPixmap(orangePixmap);
                           QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, gameField->getField(myRow - 1, myColumn - 1), SLOT(renewBlackColor()));
                       }
                  }
                  if(myColumn + 1 < Data::NUMBER_COLUMNS){
                       if(this->gameField->getField(myRow - 1, myColumn + 1)->getIsFree()){
                           this->gameField->getField(myRow - 1, myColumn + 1)->setPixmap(orangePixmap);
                           QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, gameField->getField(myRow - 1, myColumn + 1), SLOT(renewBlackColor()));
                       }
                 }
           }
      }else{
          error();
      }
    }else if(isTileOfActuelPlayer(selectedTile)){
        //there is a tile to remove. select only the free field after the adverse tile

              if(myRow + 1 < Data::NUMBER_ROWS && myColumn + 1 < Data::NUMBER_COLUMNS){
                  if(!this->gameField->getField(myRow + 1, myColumn + 1)->getIsFree()
                       && isAdverseTile(myRow + 1, myColumn + 1)){
                      if((myRow + 2 < Data::NUMBER_ROWS && myColumn + 2 < Data::NUMBER_COLUMNS)
                          && this->gameField->getField(myRow + 2, myColumn + 2)->getIsFree()){
                          this->gameField->getField(myRow + 2, myColumn + 2)->setPixmap(orangePixmap);
                          QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, this->gameField->getField(myRow + 2, myColumn + 2), SLOT(renewBlackColor()));
                      }
                  }
              }
              if(myRow + 1 < Data::NUMBER_ROWS && myColumn - 1 >= 0){
                  if(!this->gameField->getField(myRow + 1, myColumn - 1)->getIsFree()
                     && isAdverseTile(myRow + 1, myColumn - 1)){
                      if((myRow + 2 < Data::NUMBER_ROWS && myColumn - 2 >= 0)
                          && this->gameField->getField(myRow + 2, myColumn - 2)->getIsFree()){
                          this->gameField->getField(myRow + 2, myColumn - 2)->setPixmap(orangePixmap);
                          QTimer::singleShot(500, this->gameField->getField(myRow + 2, myColumn - 2), SLOT(renewBlackColor()));
                      }
                  }
              }
              if(myRow - 1 >= 0 && myColumn - 1 >= 0){
                  if(!this->gameField->getField(myRow - 1, myColumn - 1)->getIsFree()
                     && isAdverseTile(myRow - 1, myColumn - 1)){
                      if((myRow - 2 >= 0 && myColumn - 2 >= 0)
                          && this->gameField->getField(myRow - 2, myColumn - 2)->getIsFree()){
                          this->gameField->getField(myRow - 2, myColumn - 2)->setPixmap(orangePixmap);
                          QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, this->gameField->getField(myRow - 2, myColumn - 2), SLOT(renewBlackColor()));
                      }
                  }
              }
              if(myRow - 1 >= 0 && myColumn + 1 < Data::NUMBER_COLUMNS){
                  if(!this->gameField->getField(myRow - 1, myColumn + 1)->getIsFree()
                     && isAdverseTile(myRow - 1, myColumn + 1)){
                      if((myRow - 2 >= 0 && myColumn + 2 < Data::NUMBER_COLUMNS)
                          && this->gameField->getField(myRow - 2, myColumn + 2)->getIsFree()){
                          this->gameField->getField(myRow - 2, myColumn + 2)->setPixmap(orangePixmap);
                          QTimer::singleShot(Data::DELAY_TO_SHOW_DESTINATION_FIELD, this->gameField->getField(myRow - 2, myColumn + 2), SLOT(renewBlackColor()));
                      }
                  }
              }

    }else{
        error();
    }

}


Tile* GameLogic::getTileToremove(int row, int col){
    if(this->actuelPlayer->getName()== player1->getName()){
        for(int i = 0;i < Data::NUMBER_TILES; i++){
            if(player2->getTile(i)->getRow() == row && player2->getTile(i)->getColumn() == col){
                return player2->getTile(i);
            }
        }
    }else if(this->actuelPlayer->getName()== player2->getName()){
        for(int i = 0;i < Data::NUMBER_TILES; i++){
            if(player1->getTile(i)->getRow() == row && player1->getTile(i)->getColumn() == col){
                return player1->getTile(i);
            }
        }
    }else{
       return 0;
    }
}

void GameLogic::move(){
    bool hasMoved = false;
    this->destinationField = qobject_cast<Field*>(sender());
    if(this->destinationField != 0 && !this->destinationField->getIsFree()){
        this->destinationField = 0;
    }

    if (destinationField != 0 && selectedTile != 0 && this->isPossibleToMove()
            && isTileOfActuelPlayer(selectedTile) && !canTakeTile()){
        this->gameField->getField(this->selectedTile->getRow(), this->selectedTile->getColumn())->setFree(true);
        this->gameField->getField(this->selectedTile->getRow(), this->selectedTile->getColumn())->setTile(0);
        this->destinationField->setFree(false);
        gameField->getGameFieldLayout()->removeWidget(selectedTile);
        gameField->getGameFieldLayout()->addWidget(selectedTile, destinationField->getRow(), destinationField->getColumn(), Qt::AlignHCenter);
        this->selectedTile->setRow(this->destinationField->getRow());
        this->selectedTile->setColumn(this->destinationField->getColumn());
//        QString text = QString::number(this->selectedTile->getRow())+", "+QString::number(this->selectedTile->getColumn());
//        this->getGameField()->getLabelPlayer1()->setText(text);
        destinationField->setTile(selectedTile);
        this->makeKingIfPossible();
        //isTileSelected = false;
        selectedTile = 0;
        destinationField = 0;
        changeActuelPlayer();
        playMoveSound();
    }else if(destinationField != 0 && selectedTile != 0 && isTileOfActuelPlayer(selectedTile) && canTakeTile()){
        int destRow = destinationField->getRow();
        int destColumn = destinationField->getColumn();
        int selectedRow = selectedTile->getRow();
        int selectedColumn = selectedTile->getColumn();
        /*
          first look if the tile after the selected tile and before the destination's field is an adverse tile
          and alseo look if the destination field is free.
          */
        if(selectedRow + 1 < Data::NUMBER_ROWS && selectedColumn + 1 < Data::NUMBER_COLUMNS){
            if(!this->gameField->getField(selectedRow + 1, selectedColumn + 1)->getIsFree()
                 && isAdverseTile(selectedRow + 1, selectedColumn + 1)){
                if((selectedRow + 2 < Data::NUMBER_ROWS && selectedColumn + 2 < Data::NUMBER_COLUMNS)
                    && this->gameField->getField(selectedRow + 2, selectedColumn + 2)->getIsFree()
                    &&(selectedRow + 2 == destRow && selectedColumn + 2 == destColumn)){
                    this->removeTile(1, 1);
                    hasMoved = true;
                }
            }
        }
        if(!hasMoved && selectedRow + 1 < Data::NUMBER_ROWS && selectedColumn - 1 >= 0){
            if(!this->gameField->getField(selectedRow + 1, selectedColumn - 1)->getIsFree()
               && isAdverseTile(selectedRow + 1, selectedColumn - 1)){
                if((selectedRow + 2 < Data::NUMBER_ROWS && selectedColumn - 2 >= 0)
                    && this->gameField->getField(selectedRow + 2, selectedColumn - 2)->getIsFree()
                    &&(selectedRow + 2 == destRow && selectedColumn - 2 == destColumn)){
                    this->removeTile(1, -1);
                    hasMoved = true;
                }
            }
        }
        if(!hasMoved && selectedRow - 1 >= 0 && selectedColumn - 1 >= 0){
            if(!this->gameField->getField(selectedRow - 1, selectedColumn - 1)->getIsFree()
               && isAdverseTile(selectedRow - 1, selectedColumn - 1)){
                if((selectedRow - 2 >= 0 && selectedColumn - 2 >= 0)
                    && this->gameField->getField(selectedRow - 2, selectedColumn - 2)->getIsFree()
                    &&(selectedRow - 2 == destRow && selectedColumn - 2 == destColumn)){
                    this->removeTile(-1, -1);
                    hasMoved = true;
                }
            }
        }
        if(!hasMoved && selectedRow - 1 >= 0 && selectedColumn + 1 < Data::NUMBER_COLUMNS){
            if(!this->gameField->getField(selectedRow - 1, selectedColumn + 1)->getIsFree()
               && isAdverseTile(selectedRow - 1, selectedColumn + 1)){
                if((selectedRow - 2 >= 0 && selectedColumn + 2 < Data::NUMBER_COLUMNS)
                    && this->gameField->getField(selectedRow - 2, selectedColumn + 2)->getIsFree()
                    &&(selectedRow - 2 == destRow && selectedColumn + 2 == destColumn)){
                   this->removeTile(-1, 1);
                    hasMoved = true;
                }
            }
        }
    }

}

void GameLogic::removeTile(int relativeRow, int relativeColumn){
    this->gameField->getField(this->selectedTile->getRow(), this->selectedTile->getColumn())->setFree(true);
    this->gameField->getField(this->selectedTile->getRow() + relativeRow, this->selectedTile->getColumn() + relativeColumn)->setFree(true);

    this->gameField->getField(this->selectedTile->getRow(), this->selectedTile->getColumn())->setTile(0);
    this->gameField->getField(this->selectedTile->getRow() + relativeRow, this->selectedTile->getColumn() + relativeColumn)->setTile(0);

    this->destinationField->setFree(false);
    Tile * tileToRemove = getTileToremove(selectedTile->getRow() + relativeRow, selectedTile->getColumn() + relativeColumn);

    gameField->getGameFieldLayout()->removeWidget(tileToRemove);

    tileToRemove->hide();
    delete tileToRemove;
    this->makeKingIfPossible();
    gameField->getGameFieldLayout()->removeWidget(selectedTile);
    gameField->getGameFieldLayout()->addWidget(selectedTile, destinationField->getRow(), destinationField->getColumn(), Qt::AlignHCenter);
    this->selectedTile->setRow(this->destinationField->getRow());
    this->selectedTile->setColumn(this->destinationField->getColumn());
    destinationField->setTile(selectedTile);

    selectedTile = 0;

    changeActuelPlayer();
    destinationField = 0;

    this->playSelectedSound();
}

void GameLogic::makeKingIfPossible(){
    if(actuelPlayer->getName() == "player1" && destinationField->getRow() == 0){
          QPixmap greenKingTile(":/images/kingGreenTile.png");
          selectedTile->setPixmap(greenKingTile);
          selectedTile->setType("King");
     }
     if(actuelPlayer->getName() == "player2" && destinationField->getRow() == Data::NUMBER_ROWS - 1){
          QPixmap redKingTile(":/images/kingRedTile.png");
          selectedTile->setPixmap(redKingTile);
          selectedTile->setType("king");
     }
}

