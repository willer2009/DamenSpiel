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

/**
  * class which represents the main window of our application
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
        // file menu
       QMenu * fileMenu;
       //menu which contains the settings
       QMenu * settingsMenu;
       //menu which contains the help
       QMenu * helpMenu;

       //submenus of the file menu
       QAction *newGameAction;
       QAction *openAction;
       QAction *saveAction;
       QAction *saveIntoAction;
       QAction *printAction;
       QAction *quitAction;

       //submenu of the settings menu
       QAction *preferenceAction;

       //submenu of the help menu
       QAction *manualAction;
       QAction *aboutAction;

       //differents group element of the toolbar
       QToolBar *toolBarFile;
       QToolBar *toolBarSettings;
       QToolBar *toolBarHelp;

       //settings window
       Dialog *settings;

       //help window
       Manuel *manuel;

public:
       // create an object of the class Mainwindow
       MainWindow();

       // return the reference on the settings window
       Dialog* getSettingsDialog();

       //destroy the main window
       virtual ~MainWindow();

public slots:

       //void underConstruction();

       //print the game area
       void print();

       // show the about window of qt
       void about();
        // dialog which ask if you are sure you want to cancel your current game and start a new one
       void startNewGame();
       // shows the settings window
       void showSettings();

       // show the help window
       void showManuel();
        signals:
       //send a signal to restart the current game
               void restartGame();


};
#endif // MAINWINDOW_H
