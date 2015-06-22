#include "fenetretraitement.h"
#include "ui_fenetretraitement.h"

FenetreTraitement::FenetreTraitement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreTraitement)
{
    ui->setupUi(this);
}

FenetreTraitement::~FenetreTraitement()
{
    delete ui;
}
