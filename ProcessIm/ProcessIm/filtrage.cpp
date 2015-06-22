#include "filtrage.h"
#include "ui_filtrage.h"
#include "imagewindows.h"
#include <QMdiSubWindow>
#include "ImageCouleur.h"
#include "ImageClasse.h"
#include <QMessageBox>

Filtrage::Filtrage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filtrage)
{
    ui->setupUi(this);
}

Filtrage::Filtrage(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filtrage)
{

    //On récupére l'image sur laquelle on applique le traitement
    // On récupére également un pointeur sur la MDI Area dans laquelle on va afficher notre image de résultat
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;

    //On change l'ihm en fonction du type de l'image en entrée
    //Les traitements dépendent du type de l'image en entrée
    if (im_courante.isGrayscale()== false)
    {
        ui->cbType->clear();
        ui->cbType->addItem("Choix de la methode") ;
        ui->cbType->addItem("taille") ;
        ui->cbType->addItem("maxiLocaux") ;
    }

    if (im_courante.isGrayscale()== true)
    {
        ui->cbType->clear();
        ui->cbType->addItem("Choix de la methode") ;
        ui->cbType->addItem("moyennage") ;
        ui->cbType->addItem("ecart-type") ;

       ui->cb_Maz->hide();
        ui->lbl_taille->hide();
        ui->sp_Taille->hide();
        ui->lbl_Maz->hide();

    }
}

Filtrage::~Filtrage()
{
    delete ui;
}

void Filtrage::on_bout_valider_clicked()
{
    // cas où l'image est une image classe
    if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== false){
        // récupération des paramètre de l'interface
        QString methode = ui->cbType->currentText();
        int taille = ui->sp_Taille->value();
        bool Raz = ui->cb_Maz->isChecked();
        CImageCouleur im_couleur = CImageCouleur(im_courante);

        CImageClasse im_classe = CImageClasse(im_couleur,"V8");

        QImage im_aff = im_classe.GetQImageClasse();
        ImWin = new ImageWindows(im_aff, "image classe");
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();

        im_classe = im_classe.filtrage(methode.toStdString(),taille,Raz);
        im_transforme = im_classe.GetQImageClasse();
        QString nom = "Image Couleur Filtree";
        ImageWindows *ImWin2 = new ImageWindows(im_transforme, nom);
        QMdiSubWindow *subWindow2 = new QMdiSubWindow;
        subWindow2->setWidget(ImWin2);
        subWindow2->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow2);
        subWindow2->show();
    } else if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== true){
        // récupération des paramètre de l'interface
        QString methode = ui->cbType->currentText();

        CImageNdg im_ndg = CImageNdg(im_courante);
        im_ndg = im_ndg.filtrage(methode.toStdString(),3);

        im_transforme = im_ndg.GetQImageNdg();
        QString nom = "Image Ndg Filtree";
        ImageWindows *ImWin = new ImageWindows(im_transforme, nom);
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
    }else
       QMessageBox::information(this, "Error", "Probléme image vide");


}

void Filtrage::on_bout_annuler_clicked()
{

}

