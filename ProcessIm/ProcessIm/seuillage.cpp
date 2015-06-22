#include "seuillage.h"
#include "ui_seuillage.h"
#include <QMessageBox.h>


#include "ImageNdg.h"
#include "ImageCouleur.h"


Seuillage::Seuillage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Seuillage)
{
    ui->setupUi(this);
}

Seuillage::Seuillage(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Seuillage)
{
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;

    if (im_courante.isGrayscale()== false)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","La fonction seuillage ne fonctionne que pour une image Ndg");
        messageBox.setFixedSize(500,200);
        messageBox.show();

        isSeuillagePossible = false;
    }
    else
    {
        QString name_image = "Image seuillee";
        ImWin = new ImageWindows(im_courante, name_image);
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();

        isSeuillagePossible = true;
    }
}

Seuillage::~Seuillage()
{
    delete ui;
}



void Seuillage::on_hs_bas_valueChanged(int value)
{
    if(isSeuillagePossible == false)
        return;

    CImageNdg im_seuillage = CImageNdg(im_courante);
    im_seuillage = im_seuillage.seuillage("manuel", value, ui->hs_haut->value());
    im_transforme = im_seuillage.GetQImageNdg();
    ImWin->setImageCurrent(im_transforme);
}

void Seuillage::on_hs_haut_valueChanged(int value)
{
    if(isSeuillagePossible == false)
        return;

    CImageNdg im_seuillage = CImageNdg(im_courante);
    im_seuillage = im_seuillage.seuillage("manuel",ui->hs_bas->value() , value);
    im_transforme = im_seuillage.GetQImageNdg();
    ImWin->setImageCurrent(im_transforme);

}

void Seuillage::on_boutValider_clicked()
{
    if (im_courante.isGrayscale()== false)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","La fonction seuillage ne fonctionne que pour une image Ndg");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
    else
    {
        QString type = ui->comboBox->currentText();
        CImageNdg im_seuillage = CImageNdg(im_courante);
        im_seuillage = im_seuillage.seuillage(type.toStdString(),ui->hs_bas->value() , ui->hs_haut->value());
        im_transforme = im_seuillage.GetQImageNdg();
        ImWin->setImageCurrent(im_transforme);
    }
}



void Seuillage::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "automatique"){
        ui->label_4->hide();
        ui->label_5->hide();
        ui->hs_bas->hide();
        ui->hs_haut->hide();
        ui->sp_bas->hide();
        ui->sp_haut->hide();

    }else{
        ui->label_4->show();
        ui->label_5->show();
        ui->hs_bas->show();
        ui->hs_haut->show();
        ui->sp_bas->show();
        ui->sp_haut->show();

    }
}
