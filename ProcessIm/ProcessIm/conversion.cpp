#include "conversion.h"
#include "ui_conversion.h"

#include <QMessageBox>

#include "ImageCouleur.h"
#include "ImageNdg.h"

Conversion::Conversion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Conversion)
{
    ui->setupUi(this);
}

Conversion::Conversion(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Conversion)
{
    ui->setupUi(this);

    //On récupére l'image sur laquelle on applique le traitement
    // On récupére également un pointeur sur la MDI Area dans laquelle on va afficher notre image de résultat
    im_courante = im;
    m_AreaMdi = areaffichage;


    //En fonction de l'espace colorimètrique on change le nom des plans
    ui->radioButton_RGB->setChecked(true);
    ui->checkBox_0->setText("R");
    ui->checkBox_1->setText("G");
    ui->checkBox_2->setText("B");

}

Conversion::~Conversion()
{
    delete ui;
}

void Conversion::on_radioButton_HSV_clicked()
{
    if(!ui->radioButton_HSV->isChecked()){
        ui->radioButton_RGB->setChecked(true);
        ui->radioButton_HSV->setChecked(false);
        ui->checkBox_0->setText("R");
        ui->checkBox_1->setText("G");
        ui->checkBox_2->setText("B");
    }else{
        ui->radioButton_HSV->setChecked(true);
        ui->radioButton_RGB->setChecked(false);
        ui->checkBox_0->setText("H");
        ui->checkBox_1->setText("S");
        ui->checkBox_2->setText("V");
    }



}

void Conversion::on_radioButton_RGB_clicked()
{
    if(ui->radioButton_RGB->isChecked()){
        ui->radioButton_RGB->setChecked(true);
        ui->radioButton_HSV->setChecked(false);
        ui->checkBox_0->setText("R");
        ui->checkBox_1->setText("G");
        ui->checkBox_2->setText("B");
    }else{
        ui->radioButton_HSV->setChecked(true);
        ui->radioButton_RGB->setChecked(false);
        ui->checkBox_0->setText("H");
        ui->checkBox_1->setText("S");
        ui->checkBox_2->setText("V");
    }


}

void Conversion::on_pushButton_clicked()
{
    if(im_courante.isGrayscale()){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }else{
        ConversionHSV();
    }

}

void Conversion::ConversionHSV(){
    CImageCouleur im_couleur = CImageCouleur(im_courante);


    if(ui->radioButton_RGB->isChecked()){
        if(ui->checkBox_0->isChecked()){
            CImageNdg im_plan0 = im_couleur.plan(0);
            CreerImageMdiArea(im_plan0.GetQImageNdg(), m_AreaMdi, "plan R");
        }
        if(ui->checkBox_1->isChecked()){
             CImageNdg im_plan1 = im_couleur.plan(1);
             CreerImageMdiArea(im_plan1.GetQImageNdg(), m_AreaMdi, "plan G");
        }
        if(ui->checkBox_2->isChecked()){
             CImageNdg im_plan2 = im_couleur.plan(2);
             CreerImageMdiArea(im_plan2.GetQImageNdg(), m_AreaMdi, "plan B");
        }

    }else{
        im_couleur = im_couleur.conversion("HSV");
        CreerImageMdiArea(im_couleur.GetQImage(), m_AreaMdi, "HSV");



        if(ui->checkBox_0->isChecked()){
            CImageNdg im_plan0 = im_couleur.plan(0);
            CreerImageMdiArea(im_plan0.GetQImageNdg(), m_AreaMdi, "plan H");
        }
        if(ui->checkBox_1->isChecked()){
             CImageNdg im_plan1 = im_couleur.plan(1);
             CreerImageMdiArea(im_plan1.GetQImageNdg(), m_AreaMdi, "plan S");
        }
        if(ui->checkBox_2->isChecked()){
             CImageNdg im_plan2 = im_couleur.plan(2);
             CreerImageMdiArea(im_plan2.GetQImageNdg(), m_AreaMdi, "plan V");
        }
    }

}

void Conversion::CreerImageMdiArea(QImage image, QMdiArea * mdiArea, QString name_image){

    ImageWindows *ImWin = new ImageWindows(image, name_image);
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(ImWin);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(subWindow1);
    subWindow1->show();
}
