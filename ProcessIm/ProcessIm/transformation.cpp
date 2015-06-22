#include "transformation.h"
#include "ui_transformation.h"
#include "imagewindows.h"
#include <QMdiSubWindow>
#include "ImageCouleur.h"
#include <QMessageBox>

Transformation::Transformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transformation)
{
    ui->setupUi(this);
}

Transformation::Transformation(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transformation)
{
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;
}

Transformation::~Transformation()
{
    delete ui;
}

void Transformation::on_bout_valider_clicked()
{
    if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== true){
        // récupération des paramètres de l'interface
        QString methode = ui->cb_transformation->currentText();
        int seuilB = ui->sp_mini->value();
        int seuilH = ui->sp_max->value();

        CImageNdg im_ndg = CImageNdg(im_courante);
        im_ndg = im_ndg.transformation(methode.toStdString(),seuilB,seuilH);
        im_transforme = im_ndg.GetQImageNdg();
        QString nom = "Image transformation : " + methode ;
        ImageWindows *ImWin = new ImageWindows(im_transforme, nom);
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
    } else if(im_courante.isGrayscale()== false)
       QMessageBox::information(this, "Error", "L'image n'est pas une image Ndg");
    else
       QMessageBox::information(this, "Error", "Probléme image vide");


}

void Transformation::on_bout_annuler_clicked()
{

}

void Transformation::on_cb_transformation_currentIndexChanged(const QString &arg1)
{

    if(arg1 == "complement"){
        ui->label->hide();
        ui->label_2->hide();
        ui->lbl_type_morpho->hide();
        ui->lbl_type_morpho_2->hide();
        ui->lbl_type_morpho_3->hide();
        ui->slid_max->hide();
        ui->slid_mini->hide();
        ui->sp_max->hide();
        ui->sp_mini->hide();
    }else {
        ui->label->show();
        ui->label_2->show();
        ui->lbl_type_morpho->show();
        ui->lbl_type_morpho_2->show();
        ui->lbl_type_morpho_3->show();
        ui->slid_max->show();
        ui->slid_mini->show();
        ui->sp_max->show();
        ui->sp_mini->show();

    }

}
