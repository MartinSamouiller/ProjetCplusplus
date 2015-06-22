#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include "QSplitter"
#include "QMdiArea"
#include "QMdiSubWindow"
#include "QDesktopWidget"


#include "morphologie.h"
#include "transformation.h"
#include "filtrage.h"
#include "lecturecb.h"
#include "seuillage.h"
#include "distance.h"
#include "histogramme.h"
#include "comptage.h"
#include "imagewindows.h"
#include "infowindows.h"
#include "signatures.h"
#include "conversion.h"


#include "ImageNdg.h"
#include "ImageClasse.h"
#include "ImageCouleur.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setLayout(ui->Layout_Travail);

    InfoWindows *info = new InfoWindows();
    info -> setWindowModality (Qt::ApplicationModal);
    info->show();


    /*QDesktopWidget *desktop = new QDesktopWidget;
    int largeur = desktop->screenGeometry().width();
    int hauteur = desktop->screenGeometry().height();
    resize(largeur, hauteur-100);*/
    //On retaille la fenetre en plein ecran
    //showFullScreen();
    showNormal();


}

MainWindow::~MainWindow()
{
    //message
    delete ui;
}

void MainWindow::on_actionOuvrir_une_image_triggered()
{
    m_index_image += 1;
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.bmp)");
    QFileInfo file(fichier);


    QImage *im_tmp = new QImage(fichier);

    QString name_image = file.fileName();


    ImageWindows *ImWin = new ImageWindows(*im_tmp,name_image );
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(ImWin);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea->addSubWindow(subWindow1);
    subWindow1->show();

/*
    images.push_back(*im_tmp);
    image_courante = im_tmp;
    ui->cbImage->addItem("Image n°");*/


}

void MainWindow::on_actionQuitter_triggered()
{
      close();
}

void MainWindow::on_actionTutoriel_triggered()
{
    QMessageBox::information(this, "Aide", "Affiche le <strong>tutoriel<strong>");
}

void MainWindow::on_actionA_propos_de_ProcessIm_triggered()
{
    InfoWindows *info = new InfoWindows();
    info -> setWindowModality (Qt::WindowModal);
    info->show();
    //QMessageBox::information(this, "A propos", "Créateur : ...");
}


//Si erreur de externe non résolu : vérifier les dossiers build

void MainWindow::on_actionDossier_de_travail_triggered()
{

}

void MainWindow::on_cbTraitement_currentIndexChanged(const QString &arg1)
{
    //CImageNdg *image_traitement = new CImageNdg(*image_courante);

    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1 =  ui->mdiArea->currentSubWindow();
    if(subWindow1 != 0){
        ImageWindows *imCurrent = (ImageWindows*)subWindow1->widget();
            QImage imTransform = imCurrent->getImageCurrent();
            ui->lbl_curren_image_selectionner->setText(imCurrent->getImageName());

            if (arg1 == "Morphologie")
            {
               Morphologie *mor = new Morphologie(ui->mdiArea, imTransform);
               ui->sa_outil->setWidget(mor);
            }

            if (arg1 == "Transformation")
            {
               Transformation *trans = new Transformation(ui->mdiArea, imTransform);
               ui->sa_outil->setWidget(trans);
            }

            if (arg1 == "Filtrage")
            {
               Filtrage *filt = new Filtrage(ui->mdiArea, imTransform);
               ui->sa_outil->setWidget(filt);
            }
            if (arg1 == "Seuillage")
            {
                Seuillage *seuil = new Seuillage(ui->mdiArea, imTransform);
                ui->sa_outil->setWidget(seuil);

            }

            if (arg1 == "Distance au fond")
            {
                Distance *dist = new Distance(ui->mdiArea, imTransform);
                ui->sa_outil->setWidget(dist);
            }

            if (arg1 == "Histogramme")
            {
                Histogramme *histo = new Histogramme(imTransform);
                ui->sa_outil->setWidget(histo);
            }
            if (arg1 == "Conversion")
            {
                Conversion *conver = new Conversion(ui->mdiArea, imTransform);
                 ui->sa_outil->setWidget(conver);
            }
    }else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }


}


void MainWindow::on_cbAnalyse_currentIndexChanged(const QString &arg2)
{
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1 =  ui->mdiArea->currentSubWindow();
    if(subWindow1 != 0){
        ImageWindows *imCurrent = (ImageWindows*)subWindow1->widget();
        QImage imTransform = imCurrent->getImageCurrent();
        ui->lbl_curren_image_selectionner->setText(imCurrent->getImageName());

            if (arg2 == "Lecture code barre")
                {
                   LectureCB *leccb = new LectureCB(ui->mdiArea, imTransform);
                   ui->sa_outil_2->setWidget(leccb);
                }

                if (arg2 == "Comptage Objet")
                {
                   Comptage *compte = new Comptage(ui->mdiArea, imTransform);
                   ui->sa_outil_2->setWidget(compte);
                }

                if (arg2 == "Signatures")
                {
                    Signatures *signature = new Signatures(ui->mdiArea, imTransform);
                    ui->sa_outil_2->setWidget(signature);
                }

    }else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
}



void MainWindow::on_actionDistance_au_fond_triggered()
{
     ui->tabWidget->setCurrentIndex(0);
     ui->cbTraitement->setCurrentText("Distance au fond");
}

void MainWindow::on_actionFiltrage_triggered()
{
      ui->tabWidget->setCurrentIndex(0);
      ui->cbTraitement->setCurrentText("Filtrage");
}

void MainWindow::on_actionSeuillage_triggered()
{
      ui->tabWidget->setCurrentIndex(0);
      ui->cbTraitement->setCurrentText("Seuillage");
}

void MainWindow::on_actionMorphologie_triggered()
{
       ui->tabWidget->setCurrentIndex(0);
       ui->cbTraitement->setCurrentText("Morphologie");
}

void MainWindow::on_actionTransformation_triggered()
{
       ui->tabWidget->setCurrentIndex(0);
       ui->cbTraitement->setCurrentText("Transformation");
}

void MainWindow::on_actionHistogramme_triggered()
{
       ui->tabWidget->setCurrentIndex(0);
       ui->cbTraitement->setCurrentText("Histogramme");
}

void MainWindow::on_actionConversion_triggered()
{
       ui->tabWidget->setCurrentIndex(0);
       ui->cbTraitement->setCurrentText("Conversion");
}

void MainWindow::on_actionLecture_codes_barres_triggered()
{
        ui->tabWidget->setCurrentIndex(1);
        ui->cbAnalyse->setCurrentText("Lecture code barre");
}

void MainWindow::on_actionSignatures_triggered()
{
         ui->tabWidget->setCurrentIndex(1);
         ui->cbAnalyse->setCurrentText("Signatures");
}

void MainWindow::on_actionComptage_objet_triggered()
{
         ui->tabWidget->setCurrentIndex(1);
         ui->cbAnalyse->setCurrentText("Comptage Objet");
}
