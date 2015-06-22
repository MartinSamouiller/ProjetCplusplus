#include "comptage.h"
#include "ui_comptage.h"
#include "ImageClasse.h"
#include "ImageCouleur.h"
#include "ImageNdg.h"
#include <QMessageBox>

Comptage::Comptage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comptage)
{
    ui->setupUi(this);
}

Comptage::Comptage(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comptage)
{

    //On récupére l'image sur laquelle on applique le traitement
    // On récupére également un pointeur sur la MDI Area dans laquelle on va afficher notre image de résultat
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;


    if (im_courante.isGrayscale()== true)
    {
        ui->lblType->setText("Image Ndg");
        ui->lblPlan->hide();
        ui->cbPlan->hide();

    }

    if (im_courante.isGrayscale()== false)
    {
        ui->lblType->setText("Image couleur (3 plans)");
    }
}

Comptage::~Comptage()
{
    delete ui;

}

//Validation du traitement
void Comptage::on_BoutValider_clicked()
{

    //
    if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== true){
        // récupération des paramètre de l'interface

        CImageNdg im_ndg = CImageNdg(im_courante);
        im_ndg = im_ndg.seuillage("automatique");
        //im_ndg = im_ndg.transformation("complement");



        ///
        CImageClasse im_classe = CImageClasse(im_ndg,"V8" );
        im_classe = im_classe.filtrage("taille",200);

        CImageClasse im_classe_tmp = CImageClasse(im_classe, "avec", "V8" );

        //im_classe = im_classe.croissanceRegion(im_ndg,0,0,0);

        //affichage de l'image classe
        QImage im_aff = im_classe_tmp.GetQImageClasse();
        ImWin = new ImageWindows(im_aff, "image classe");
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();

        int resultat = im_classe_tmp.lireNbRegions();
        QString res = QString::number(resultat);
        ui->lblRes->setText(res);
    }
    else
       QMessageBox::information(this, "Error", "Probléme image vide");
}

void Comptage::on_cbPlan_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Plan 0 : Rouge")
        {
        QString name_image = "Image Plan Rouge";
        CImageCouleur im_Pr0 = im_courante;
        CImageNdg im_ndg = im_Pr0.plan(0);
        QImage im_aff = im_ndg.GetQImageNdg();
        ImWin = new ImageWindows(im_aff, name_image);
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
        im_courante = im_aff;
        }

    if (arg1 == "Plan 1 : Vert")
        {
        QString name_image = "Image Plan Vert";
        CImageCouleur im_Pr0 = im_courante;
        CImageNdg im_ndg = im_Pr0.plan(1);
        QImage im_aff = im_ndg.GetQImageNdg();
        ImWin = new ImageWindows(im_aff, name_image);
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
        im_courante = im_aff;

        }

    if (arg1 == "Plan 2 : Bleu")
        {
        QString name_image = "Image Plan Bleu";
        CImageCouleur im_Pr0 = im_courante;
        CImageNdg im_ndg = im_Pr0.plan(2);
        QImage im_aff = im_ndg.GetQImageNdg();
        ImWin = new ImageWindows(im_aff, name_image);
        subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
        im_courante = im_aff;
        }
}
