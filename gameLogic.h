#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GameField.h"
#include "MainWindow.h"

class GameLogic: public QObject{
    Q_OBJECT
private:
    Player *player1;
    Player *player2;
    Player *actuelPlayer;
    GameField *gameField;
    MainWindow *mainWindow;
    bool hasStarted;
    bool hasTerminated;
    Player winner;
    Field *destinationField;
    Tile *selectedTile;
    bool isTileSelected;
    int numberRemovedTile;
    //bool somethingHasChanged;

public:
    GameLogic(Player *p1, Player *p2, GameField *gameField, MainWindow *mainWindow);

    //Player* getPlayer1();

   // Player* getPlayer2();

   // GameField* getGameField();



    bool isPossibleToMove();

    void selectDestination();

    QString getNormalDirection(Tile * tile);

    Player* chooseFirstPlayer();

    void changeActuelPlayer();

    Tile* getTileToremove(int i, int j);

    void removeTile(int relativeRow, int relativeColumn);

    void makeKingIfPossible();

    /**
      *  tell you if there is an adverse tile to take or not
     **/
    bool canTakeTile();

    bool isAdverseTile(int i, int j);

    bool isTileOfActuelPlayer(Tile *tile);

    //bool canTakeTileSomewhere();

    //bool canTakeTile(Tile *selectedTile);

    void setTime(QLabel* label);

    void start();

    void playSelectedSound();

    void playMoveSound();

    void error();

public slots:
        void selectTile();
        void move();
        void selectDest();
        void selectPossibleNeighborsWhereToPlay();
        void restart();
        void hideOrShowCurrentPlayer();
        void checkDialogState();
        //void changeActualPlayerBecauseOfTimeOut();


signals:
        void clicked();

};

#endif // GAME_H
