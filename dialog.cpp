#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

/*void Dialog::on_buttonBox_accepted(){
    if(ui->checkBox->checkState() == Qt::Checked){
        emit showCurrentPlayer();
    }else{
        emit hideCurrentPlayer();
    }
}*/
bool Dialog::getStatus(){
    if(this->ui->checkBox->checkState() == Qt::Checked){
        return true;
    }else{
        return false;
    }
}

void Dialog::check(){
  ui->checkBox->setChecked(true);
}

void Dialog::uncheck(){
    ui->checkBox->setChecked(false);
}
