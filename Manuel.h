#ifndef MANUEL_H
#define MANUEL_H

#include <QDialog>

namespace Ui {
    class Manuel;
}

class Manuel : public QDialog
{
    Q_OBJECT

public:
    explicit Manuel(QWidget *parent = 0);
    ~Manuel();

private:
    Ui::Manuel *ui;
};

#endif // MANUEL_H
