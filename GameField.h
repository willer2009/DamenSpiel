#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include<QtGui>

#include"Field.h"
#include <QMouseEvent>
#include<QFont>

class GameField : public QWidget
{
    Q_OBJECT
public:
    GameField();

    void mousePressEvent(QMouseEvent *ev);
    Field* getField(int i, int j);
    QGridLayout* getGameFieldLayout();
    QLabel *getLabelPlayer1();

    void setLabelPlayer1(QString text);
    ~GameField();

private:

    Field *fields[10][10];

    QGridLayout *gameFieldLayout;

    QGridLayout *borderLayout;

    QLabel *labelPlayer1;

public slots:
    //void selectPossibleNeighbors();

signals:
    void clicked();
};

#endif // GAMEFIELD_H
