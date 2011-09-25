#ifndef TILE_H
#define TILE_H

#include<QtGui>

class Tile : public QLabel{
    Q_OBJECT
public:
    Tile(QString type, int row, int Column, QString playerName);
    QString getType();
    QString getPlayerName();
    int getRow();
    int getColumn();

    void setType(QString newType);
    void setRow(int newRow);
    void setColumn(int newColumn);
    void setPlayerName(QString newPlayerName);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void clicked();

public slots:
    //void selectMe();

private:

    QString type;
    int row;
    int column;
    QString playerName;


};

#endif // TILE_H
