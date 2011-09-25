#include "manuel.h"
#include "ui_manuel.h"

Manuel::Manuel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manuel)
{
    ui->setupUi(this);
}

Manuel::~Manuel()
{
    delete ui;
}
