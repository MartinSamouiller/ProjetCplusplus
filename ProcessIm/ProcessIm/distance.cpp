#include "distance.h"
#include "ui_distance.h"
#include "ImageClasse.h"
#include "ImageCouleur.h"
#include "ImageNdg.h"

#include "imagewindows.h"
#include <QMdiSubWindow>

#include <QMessageBox>

Distance::Distance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Distance)
{
    ui->setupUi(this);
}

Distance::Distance(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Distance)
{
    ui->setupUi(this);

    //On récupére l'image sur laquelle on applique le traitement
    // On récupére également un pointeur sur la MDI Area dans laquelle on va afficher notre image de résultat
    im_courante = im;
    m_AreaMdi = areaffichage;

    /*if(im_courante.isGrayscale())
        ui->groupBox->setVisible(false);*/
}


Distance::~Distance()
{
    delete ui;
}

void Distance::on_boutValider_clicked()
{
    if(im_courante.isGrayscale()){
        CImageNdg im_1_Plan = CImageNdg(im_courante);
        //im_1_Plan = im_1_Plan.transformation("complement");
        //CImageClasse croisreg = croisreg.croissanceRegion(im_1_Plan, 0, 0, ui->doubleSpinBox_tolerance->value());

        //CreerImageMdiArea(croisreg.GetQImageClasse(), m_AreaMdi, "Image seuillee");
        CImageClasse im_classe_di = CImageClasse(im_1_Plan, "V8");
        CImageClasse im_distance = im_classe_di.distance(ui->comboBox->currentText().toStdString(), 0);
        im_transforme = im_distance.GetQImageClasse();
        CreerImageMdiArea(im_transforme, m_AreaMdi, "Image Distance au fond");

        ui->lbl_distancemax->setText(QString::number(im_distance.lireNbRegions()));

    } else
    {

        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();

        /*CImageCouleur im_couleur = CImageCouleur(im_courante);
        CImageNdg img_ndg =  im_couleur.plan(0);
        if( ui->radioButton_R->isChecked()){
            img_ndg =  im_couleur.plan(0);
        }
        else if( ui->radioButton_V->isChecked()){
            img_ndg =  im_couleur.plan(1);
        }
        else if(ui->radioButton_B->isChecked()){
            img_ndg =  im_couleur.plan(2);
        }
        else{
           img_ndg =  im_couleur.plan(3);
        }
        img_ndg = img_ndg.seuillage("automatique");

        CImageClasse croisreg = croisreg.croissanceRegion(img_ndg, 0, 0, ui->doubleSpinBox_tolerance->value());
        CImageClasse pieces(croisreg.mutation().transformation("complement"), "V8");
        CImageClasse im_distance = pieces.distance(ui->comboBox->currentText().toStdString(), 0);
        im_transforme = im_distance.GetQImageClasse();

        CreerImageMdiArea(im_transforme, m_AreaMdi, "Image distance au fond");*/

    }


}


//Permet de creer une image directement dans la MDi Area
void Distance::CreerImageMdiArea(QImage image, QMdiArea * mdiArea, QString name_image){

    ImageWindows *ImWin = new ImageWindows(image, name_image);
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(ImWin);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}



