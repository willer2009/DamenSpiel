#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include<QMessageBox>
#include "Data.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "dialog.h"
#include "Manuel.h"

//#include "gameLogic.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

       //GameLogic * gameLogic;
       QMenu * fileMenu;
       //QMenu * editMenu;
       QMenu * settingsMenu;
       QMenu * helpMenu;

       QAction *newGameAction;
       QAction *openAction;
       QAction *saveAction;
       QAction *saveIntoAction;
       QAction *printAction;
       QAction *quitAction;

       // QAction *undoAction;
       //QAction *redoAction;

       QAction *preferenceAction;

       QAction *manualAction;
       QAction *aboutAction;

       QToolBar *toolBarFile;
       //QToolBar *toolBarEdit;
       QToolBar *toolBarSettings;
       QToolBar *toolBarHelp;

       Dialog *settings;
       Manuel *manuel;

public:
       MainWindow();
       Dialog* getSettingsDialog();
       virtual ~MainWindow();

public slots:
               void underConstruction();
               void print();
               void about();
               void startNewGame();
               void showSettings();
               void showManuel();
        signals:
               void restartGame();
               //void signalChangeCurrentPlayer();

};
#endif // MAINWINDOW_H
