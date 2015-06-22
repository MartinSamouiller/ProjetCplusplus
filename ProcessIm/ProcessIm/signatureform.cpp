#include "signatureform.h"
#include "ui_signatureform.h"

#include <QLabel>

SignatureForm::SignatureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignatureForm)
{
    ui->setupUi(this);
}

SignatureForm::SignatureForm(std::vector<SIGNATURE_Forme> sign,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignatureForm)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(sign.size());
    for(int i = 0; i< sign.size(); i++){
        QLabel *scentreGravite_i = new QLabel(QString::number(sign.at(i).centreGravite_i));
        ui->tableWidget->setCellWidget(i, 0, scentreGravite_i);

        QLabel *scentreGravite_j = new QLabel(QString::number(sign.at(i).centreGravite_j));
        ui->tableWidget->setCellWidget(i, 1, scentreGravite_j);

        QLabel *ssurface = new QLabel(QString::number(sign.at(i).surface));
        ui->tableWidget->setCellWidget(i, 2, ssurface);

        QLabel *scodeFreeman = new QLabel(QString(sign.at(i).codeFreeman.c_str()));
        ui->tableWidget->setCellWidget(i, 3, scodeFreeman);

        QLabel *spremierPt_i = new QLabel(QString::number(sign.at(i).premierPt_i));
        ui->tableWidget->setCellWidget(i, 4, spremierPt_i);

        QLabel *spremierPt_j = new QLabel(QString::number(sign.at(i).premierPt_j));
        ui->tableWidget->setCellWidget(i, 5, spremierPt_j);

        QLabel *srectEnglob_Hi = new QLabel(QString::number(sign.at(i).rectEnglob_Hi));
        ui->tableWidget->setCellWidget(i, 6, srectEnglob_Hi);

        QLabel *srectEnglob_Hj = new QLabel(QString::number(sign.at(i).rectEnglob_Hj));
        ui->tableWidget->setCellWidget(i, 7, srectEnglob_Hj);

        QLabel *srectEnglob_Bi = new QLabel(QString::number(sign.at(i).rectEnglob_Bi));
        ui->tableWidget->setCellWidget(i, 8, srectEnglob_Bi);

        QLabel *srectEnglob_Bj = new QLabel(QString::number(sign.at(i).rectEnglob_Bj));
        ui->tableWidget->setCellWidget(i, 9, srectEnglob_Bj);

        QLabel *sperimetre = new QLabel(QString::number(sign.at(i).perimetre));
        ui->tableWidget->setCellWidget(i, 10, sperimetre);

    }
}


SignatureForm::~SignatureForm()
{
    delete ui;
}
