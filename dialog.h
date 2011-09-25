#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    bool getStatus();
    void check();
    void uncheck();
    ~Dialog();

private:
    Ui::Dialog *ui;
public slots:
    //virtual void  accept();

/*signals:
    showCurrentPlayer();
    hideCurrentPlayer();*/
};

#endif // DIALOG_H
