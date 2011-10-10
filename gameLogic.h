#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GameField.h"
#include "MainWindow.h"
#include <phonon/phonon>

/**
  * class which represents the logic of the game, it knows what to do and when it has to be done
  */
class GameLogic: public QObject{
    Q_OBJECT
private:
    // represents the player 1
    Player *player1;
    // represents the player 2
    Player *player2;
    //represents the current player in the game(player who has to play)
    Player *actuelPlayer;
    //represents the game area
    GameField *gameField;
    //represents the main window of the game
    MainWindow *mainWindow;
    //represents the reference on the destination field
    Field *destinationField;
    //represents the reference on the current selected tile
    Tile *selectedTile;
    // is true if the current selected tile has to remove another adverse tile and false else
    bool takeAlsoTheNextTile;

public:
    //create a new object of the class Gamelogic
    GameLogic(Player *p1, Player *p2, GameField *gameField, MainWindow *mainWindow);

    //shows a dialog which contains the name of the winner when there is one
    void showTheWinnerIfThereIsOne();

    // return true if the selected tile can move to the choosen destination
    bool isPossibleToMove();

    //select the destination field where to move
    void selectDestination();

    // return the direction of the tile, either from top to the bottom or from the bottom to the top
    QString getNormalDirection(Tile * tile);

    //choose the first player who starts to play
    Player* chooseFirstPlayer();

    //change the current player with the other one
    void changeActuelPlayer();

    //returns the tile which will be removed at the given row and column
    Tile* getTileToremove(int row, int column);

    //remove the tile which is at a relative position to the selected tile. the relative position is given as parameter
    void removeTile(int relativeRow, int relativeColumn);

    //make a king with the current tile if it has arrived the last adverse line
    void makeKingIfPossible();

    //returns true if there is an adverse tile to take and false else
    bool canTakeTile();

    //returns true if the tile at the given position is is an adverse tile and false else
    bool isAdverseTile(int i, int j);

    //returns true if the given tile is a tile of the current player
    bool isTileOfActuelPlayer(Tile *tile);

    //start a new game after the creation of the game logic
    void start();

    //play a sound when a valid tile is selected
    void playSelectedSound();

    //play a sound when a tile is moved
    void playMoveSound();

    //play an error sound when a not valid tile is selected
    void playErrorSound();

    //update the number of removed tile which is shown
    void updateNumberRemovedTile();

    //destroy the game logic object
    virtual ~GameLogic();

public slots:

        //select a tile when it is clicked
        void selectTile();
        //move the selected tile
        void move();
        //select the destination field
        void selectDest();
        //show the possible neighbor fields where it is possible to play
        void selectPossibleNeighborsWhereToPlay();
        //restart the game
        void restart();
        // hide or show the current player
        void hideOrShowCurrentPlayer();
        //check if we have to show or hide the current player during the game
        void checkDialogState();

signals:
       // void clicked();

};

#endif // GAME_H
