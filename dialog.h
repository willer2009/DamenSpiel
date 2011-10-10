#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}
/**
  * class which represents the dialog window to ask if we want to always show the current player during the gameplay
  */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    /**
      *    return true if the checkBox is checked and false if not
      */
    bool getStatus() const;

    /**
      *    check the checkbox
      */
    void check();

    /**
      *    uncheck the checkbox
      */
    void uncheck();
    ~Dialog();

private:
    Ui::Dialog *ui;
public slots:

};

#endif // DIALOG_H
