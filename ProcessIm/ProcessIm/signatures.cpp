#include "signatures.h"
#include "ui_signatures.h"

#include "imagewindows.h"


#include "ImageClasse.h"
#include "ImageCouleur.h"
#include "ImageNdg.h"

#include "signatureform.h"

Signatures::Signatures(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signatures)
{
    ui->setupUi(this);
}

 Signatures::Signatures(QMdiArea *areaffichage, QImage im, QWidget *parent) :
     QWidget(parent),
     ui(new Ui::Signatures)
 {
     ui->setupUi(this);
     im_courante = im;
     m_AreaMdi = areaffichage;
 }

Signatures::~Signatures()
{
    delete ui;
}

void Signatures::on_pushButton_Valider_clicked()
{
    if(im_courante.format() == QImage::Format_Indexed8 ){
        CImageNdg im_seuil = CImageNdg(im_courante);
        CImageClasse im_classe = CImageClasse(im_seuil,"V8" );

        QString name_image = "Image classe";
        ImageWindows *ImWin = new ImageWindows(im_classe.GetQImageClasse(), name_image);
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(ImWin);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow1);
        subWindow1->show();

        std::vector<SIGNATURE_Forme> sign_Classe = im_classe.signatures();
        SignatureForm *ihm_signature = new SignatureForm(sign_Classe);
        QMdiSubWindow *subWindow_sign = new QMdiSubWindow;
        subWindow_sign->setWidget(ihm_signature);
        subWindow_sign->setAttribute(Qt::WA_DeleteOnClose);
        m_AreaMdi->addSubWindow(subWindow_sign);
        subWindow_sign->show();



    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Necessite d'avoir une image seuillee");
        messageBox.setFixedSize(500,200);
        messageBox.show();


    }
}
