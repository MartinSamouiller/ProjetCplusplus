#include "lecturecb.h"
#include "ui_lecturecb.h"

#include "imagewindows.h"
#include <QMdiSubWindow>
#include "ImageCouleur.h"
#include <QMessageBox>
#include "ImageClasse.h"


LectureCB::LectureCB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LectureCB)
{
    ui->setupUi(this);
}

LectureCB::LectureCB(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LectureCB)
{
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;
}

LectureCB::~LectureCB()
{
    delete ui;
}

void LectureCB::on_BoutValider_clicked()
{
    if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== true ){
        // récupération des paramètres de l'interface

        CImageNdg im_ndg = CImageNdg(im_courante);
        CImageClasse im_classe = CImageClasse(im_ndg, "V8");

        std::string resultat = im_classe.LectureCDB(im_ndg);

        ui->lblRes->setText(QString(resultat.c_str()));

    } else if(im_courante.isGrayscale()== false)
       QMessageBox::information(this, "Error", "L'image n'est pas une image Ndg");
    else
       QMessageBox::information(this, "Error", "Probléme image vide");
}
