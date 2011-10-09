#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include<QtGui>

#include"Field.h"
#include <QMouseEvent>
#include <QFont>
#include "Data.h"

class GameField : public QWidget
{
    Q_OBJECT


private:
    //array which contains all the field of the game field
    Field *fields[10][10];

    //Layout on which the diferrents fields are classified and shown
    QGridLayout *gameFieldLayout;

    //Layout wich contains the borders of the game field and the game field itself
    QGridLayout *borderLayout;

    //Label which schows who has to play
    QLabel *labelActuelPlayer;

    //Label which shows how many adverse tiles the first player has removed
    QLabel *removedTilePlayer1;

   //Label which shows how many adverse tiles the second player has removed
    QLabel *removedTilePlayer2;


public:
    //create the game area
    GameField();

    //this function is called when the mouse is
    //void mousePressEvent(QMouseEvent *ev);#

    //return the reference of the field at the row i and the column j.
    Field* getField(int i, int j);

    //return the reference on the central layout which contains the diffrents fields
    QGridLayout* getGameFieldLayout();

    //return the reference on the Label which shows the current player
    QLabel *getLabelActuelPlayer();

    //change the text on the label which show the current player. The new value is the one which is given as parameter
    void setLabelActuelPlayer(QString text);

    //destroy the game area
    virtual ~GameField();

signals:
    //void clicked();
};

#endif // GAMEFIELD_H
