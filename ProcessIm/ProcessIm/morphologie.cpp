#include "morphologie.h"
#include "ui_morphologie.h"
#include "ImageNdg.h"

#include "imagewindows.h"
#include <QMdiSubWindow>

#include <QMessageBox>

Morphologie::Morphologie(/*CImageNdg *imageNdg, */QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Morphologie)
{
    ui->setupUi(this);
}

Morphologie::Morphologie(QMdiArea *areaffichage, QImage im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Morphologie)
{
    ui->setupUi(this);
    im_courante = im;
    m_AreaMdi = areaffichage;
}

Morphologie::~Morphologie()
{
    delete ui;
}



void Morphologie::on_bout_valider_clicked()
{
    if(im_courante.isNull() != true && m_AreaMdi != NULL && im_courante.isGrayscale()== true ){
        // récupération des paramètres de l'interface
        QString methode = ui->cb_TypeMorpho->currentText();
        QString ES = ui->cb_ESMorpho->currentText();

        CImageNdg im_ndg = CImageNdg(im_courante);
        im_ndg = im_ndg.morphologie(methode.toStdString(),ES.toStdString());
        im_transforme = im_ndg.GetQImageNdg();
        QString nom = "Image " + methode;
        ImageWindows *ImWin = new ImageWindows(im_transforme, nom);
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();
    }else if(im_courante.isGrayscale()== false)
       QMessageBox::information(this, "Error", "L'image n'est pas une image Ndg");
    else
       QMessageBox::information(this, "Error", "Probléme image vide");
}
