
#include "MainWindow.h"


MainWindow::MainWindow()
{
    this->setFixedSize(Data::WIDTH_GAMEFIELD, Data::HEIGHT_GAMEFIELD);

    QPixmap pixmapForIcon(":/images/damenIcon.png");
    QIcon icon(pixmapForIcon);
    this->setWindowIcon(icon);

    this->fileMenu = menuBar()->addMenu("&File");
   // this->editMenu = menuBar()->addMenu("&Edit");
    this->settingsMenu = menuBar()->addMenu("&Settings");
    this->helpMenu = menuBar()->addMenu("&Help");

    this->newGameAction = new QAction("&New", this);
    this->newGameAction->setShortcut(Qt::CTRL + Qt::Key_N);
    this->fileMenu->addAction(newGameAction);
    connect(this->newGameAction, SIGNAL(triggered()), this, SLOT(startNewGame()));
    newGameAction->setIcon(QIcon(":/images/10.png"));

    this->openAction = new QAction("&Open", this);
    this->openAction->setShortcut(Qt::CTRL + Qt::Key_N);
    this->fileMenu->addAction(openAction);
    openAction->setIcon(QIcon(":/images/Folder.png"));
    openAction->setDisabled(true);

    this->saveAction = new QAction("&Save", this);
    this->saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    this->fileMenu->addAction(saveAction);
    saveAction->setIcon(QIcon(":/images/floppy_disk.png"));
    saveAction->setDisabled(true);

    this->saveIntoAction = new QAction("S&ave as", this);
    this->saveIntoAction->setShortcut(Qt::CTRL + Qt::Key_A);
    this->fileMenu->addAction(saveIntoAction);
    saveIntoAction->setIcon(QIcon(":/images/9.png"));
    saveIntoAction->setDisabled(true);

    this->printAction = new QAction("&Print", this);
    this->printAction->setShortcut(Qt::CTRL + Qt::Key_P);
    this->fileMenu->addAction(printAction);
    connect(this->printAction, SIGNAL(triggered()), this, SLOT(print()));
    printAction->setIcon(QIcon(":/images/printer.png"));

    this->quitAction = new QAction("&Quit", this);
    this->quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    this->fileMenu->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    quitAction->setIcon(QIcon(":/images/8.png"));

//    this->undoAction = new QAction("&Undo", this);
//    this->undoAction->setShortcut(Qt::CTRL + Qt::Key_U);
//    this->editMenu->addAction(undoAction);
//    connect(undoAction, SIGNAL(triggered()), this, SLOT(underConstruction()));
//    undoAction->setIcon(QIcon(":/images/Arrow_left.png"));

//    this->redoAction = new QAction("&Redo", this);
//    this->redoAction->setShortcut(Qt::CTRL + Qt::Key_R);
//    this->editMenu->addAction(redoAction);
//    connect(redoAction, SIGNAL(triggered()), this, SLOT(underConstruction()));
//    redoAction->setIcon(QIcon(":/images/Arrow_right.png"));

    this->preferenceAction = new QAction("&Preferences", this);
    this->preferenceAction->setShortcut(Qt::CTRL + Qt::Key_P);
    this->settingsMenu->addAction(preferenceAction);
    connect(preferenceAction, SIGNAL(triggered()), this, SLOT(showSettings()));
    preferenceAction->setIcon(QIcon(":/images/Gears.png"));

    this->manualAction = new QAction("&Manual", this);
    this->manualAction->setShortcut(Qt::CTRL + Qt::Key_M);
    this->helpMenu->addAction(manualAction);
    connect(manualAction, SIGNAL(triggered()), this, SLOT(showManuel()));
    manualAction->setIcon(QIcon(":/images/Book.png"));

    this->aboutAction = new QAction("A&bout", this);
    this->aboutAction->setShortcut(Qt::CTRL + Qt::Key_B);
    this->helpMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    this->aboutAction->setIcon(QIcon(":/images/Question_mark.png"));

    //setCentralWidget(gameField);
    //toolbar
    toolBarFile = addToolBar("File");
    toolBarFile->addAction(newGameAction);
    toolBarFile->addAction(openAction);
    toolBarFile->addAction(saveAction);
    toolBarFile->addAction(printAction);

//    toolBarEdit = addToolBar("Edit");
//    toolBarEdit->addAction(undoAction);
//    toolBarEdit->addAction(redoAction);

    toolBarSettings = addToolBar("Settings");
    toolBarSettings->addAction(preferenceAction);

    toolBarHelp = addToolBar("help");
    toolBarHelp->addAction(manualAction);
    toolBarHelp->addAction(aboutAction);

    settings = new Dialog(this);
    manuel = new Manuel(this);

}

void MainWindow::underConstruction(){
    QMessageBox::warning(this, "test", "under Construction", 0, 0, 0);

}

void MainWindow::about(){
    QMessageBox::aboutQt(this, tr("About"));

}

void MainWindow::print(){

    QPrinter printer;
    QPainter painter;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("print Document"));
    dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if(dialog->exec() == QPrintDialog::Accepted){
        painter.begin(&printer);
        double xscale = printer.pageRect().width()/double(this->width());
        double yscale = printer.pageRect().height()/double(this->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                          printer.paperRect().y() + printer.pageRect().height()/2);
        painter.scale(scale, scale);
        painter.translate(-width()/2, -height()/2);

        QPixmap image(this->size());
        this->render(&image);
        painter.drawPixmap(0, 0, image);
        painter.end();
    }

}

void MainWindow::startNewGame(){
    int response = QMessageBox::question(this, tr("New game"),
                                         tr("Are you sure you want to start a new game? Your current game will be lost.")
                                         , QMessageBox::Yes | QMessageBox::No);
    if(response){
        //send a signal to the logic to restart the game
        emit restartGame();
    }

}

void MainWindow::showSettings(){
    settings->exec();
}
void MainWindow::showManuel(){
    manuel->exec();
}

//void MainWindow::changeCurrentPlayer(){
//    emit signalChangeCurrentPlayer();
//}

Dialog* MainWindow::getSettingsDialog(){
   return settings;
}
