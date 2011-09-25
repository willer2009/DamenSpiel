#include <QApplication>
#include <QtGui>
#include "MainWindow.h"
#include "GameField.h"
#include "gameLogic.h"
#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameField *gameField = new GameField;

    Player *player1 = new Player("player1", Qt::green, "toTheTop");
    Player *player2 = new Player("player2", Qt::gray, "toTheBottom");

    MainWindow *fenetre = new MainWindow();

    QRect desktopRect(QApplication::desktop()->screenGeometry());
    int xPos = desktopRect.width()/2 - fenetre->width()/2;
    int yPos = desktopRect.height()/2 - fenetre->height()/2;
    fenetre->move(xPos, yPos);

    GameLogic *gameLogic = new GameLogic(player1, player2, gameField, fenetre);
    gameLogic->start();

    fenetre->show();

    return app.exec();
}
