#include "histogramme.h"
#include "ui_histogramme.h"

#include "imagewindows.h"
#include <QMdiSubWindow>

#include "ImageNdg.h"
#include "ImageCouleur.h"

Histogramme::Histogramme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogramme)
{
    ui->setupUi(this);
}

Histogramme::Histogramme(QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogramme)
{
    ui->setupUi(this);
    im_courante = im;
}

Histogramme::~Histogramme()
{
    delete ui;
}



void Histogramme::on_boutValider_clicked()
{

    if(im_courante.isGrayscale()){

        CImageNdg image_ndg = CImageNdg(im_courante);
        std::vector<unsigned long> h = image_ndg.histogramme(ui->checkBox->isChecked());

        m_scene = new QGraphicsScene(this);   // création scene
        m_scene->clear();

        QBrush brosseBleue(Qt::blue);   // création brosse bleue
        QPen crayon(Qt::black);   // création crayon
        crayon.setWidth(2);  // taille crayon

       // m_rectangle = m_scene->addRect(0,0,10,100,crayon,brosseBleue);

        //Permet de recaler l'histogramme en fonction de la hauteur max de la fenetre
        int val_histMax = ui->graphicsView_histo->height();

        int MaxHisto = 0;

        //recherche du pic maximum dans l'histogramme -> permet de redefinir en hauteur l'histogramme
        for(int i = 0; i<h.size(); i++){
            if(MaxHisto < h[i])
                MaxHisto = h[i];
        }
        int res = 0;
        int pas = ui->graphicsView_histo->width()/256;
        qDebug() << ui->graphicsView_histo->width();

        //Creation de l'histogramme (on ajoute un rectangle de largeur variable -> depend de la largeur de la fenetre)
        int y = 0;
        for (int i=0;i<256;i++){
            res = h[i]*val_histMax/MaxHisto;
            m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(pas, -res)));
            y = y +pas;
        }

        ui->graphicsView_histo->setScene(m_scene);
    }else{
        CImageCouleur image_couleur = CImageCouleur(im_courante);
        std::vector<std::vector<unsigned long>> h = image_couleur.histogramme(ui->checkBox->isChecked());

        m_scene = new QGraphicsScene(this);   // création scene
        m_scene->clear();

        QBrush brosseBleue(Qt::blue);   // création brosse bleue

       // m_rectangle = m_scene->addRect(0,0,10,100,crayon,brosseBleue);

        int val_histMax = ui->graphicsView_histo->height();

        int MaxHisto = 0;
        for(int y = 0; y<3; y++){
            for(int i = 0; i<h.size(); i++){
                if(MaxHisto < h[y][i])
                    MaxHisto = h[y][i];
            }
        }

        int res = 0;
        int pas = ui->graphicsView_histo->width()/256;
        int y = 0;


        //On créer les histogrammes sur les 3 plans
        QPen crayon(Qt::red);   // création crayon
        for (int i=0;i<256;i++){
            res = h[0][i]*val_histMax/MaxHisto;
            m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(pas, -res)),crayon );
            y = y +pas;
        }
        y = 0;
        QPen crayon2(Qt::green);   // création crayon
        for (int i=0;i<256;i++){
            res = h[1][i]*val_histMax/MaxHisto;
            m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(pas, -res)), crayon2);
            y = y +pas;
        }
        y = 0;
        QPen crayon3(Qt::blue);   // création crayon
        for (int i=0;i<256;i++){
            res = h[2][i]*val_histMax/MaxHisto;
            m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(pas, -res)), crayon3);
            y = y +pas;
        }

        ui->graphicsView_histo->setScene(m_scene);

        //Possibilitités d'ajout :
        // choisir sur quels plan on affiche l'histogramme
        // a partir d'une combobox -> R G ou B

    }


}
