#include "imagewindows.h"
#include "ui_imagewindows.h"
#include "QSplitter"
#include "QPushButton"
#include "QFileDialog"
#include <iostream><
#include "ImageCouleur.h"


ImageWindows::ImageWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWindows)
{
    ui->setupUi(this);

}


ImageWindows::ImageWindows(QImage image, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWindows)
{
    ui->setupUi(this);

    imageLbl=new qlabel_image();

    //Signal émit par la class qlabel_image pour la lecture en dynamique de la position des pixels
    connect(imageLbl, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(imageLbl, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    connect(imageLbl, SIGNAL(Mouse_ClickLeft()), this, SLOT(MouseClickLeft()));
    connect(imageLbl, SIGNAL(Mouse_ReleasePos()), this, SLOT(Mouse_release_pos()));
    imageLbl->setMouseTracking(true);

   // setFixedHeight(image.height());
   // setFixedWidth(image.width());
    image_ihm = image;
    m_coeffZoom=1;
    affichageImage(image_ihm,m_coeffZoom,ui->scrollArea_Image);
     /*QLabel *imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Base);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel->setScaledContents(true);
     imageLabel -> setPixmap(QPixmap::fromImage(image));
     ui->scrollArea_Image->setBackgroundRole(QPalette::Dark);
     ui->scrollArea_Image->setWidget(imageLabel);

*/
    //ui ->label_Image -> setPixmap(QPixmap::fromImage(*image));
    QString txt =  QString::number(image.width())  + " x " + QString::number(image.height());
    ui->lbl_imageSize->setText(txt);

    if(image_ihm.isGrayscale())
        ui->lbl_imageDepth->setText("niveau de gris");
    else
        ui->lbl_imageDepth->setText("couleur");




    /*int index = pathImage.lastIndexOf("/");
    std::cout << "index : " << index;
    m_StrImageName = pathImage.left(index);*/
    m_StrImageName = name;
    setWindowTitle(m_StrImageName);


    QPixmap pixmap("actions/document-save-3.ico");
    QIcon ButtonIcon(pixmap);
    ui->pushB_Save->setIcon(ButtonIcon);
    QSize size = pixmap.rect().size();
    size.setHeight(size.height() -10);
    size.setWidth(size.width() -10);
    ui->pushB_Save->setIconSize(size);


    QPixmap pixmap2("actions/zoom-in-3.ico");
    QIcon ButtonIcon2(pixmap2);
    ui->pushB_ZoomIn->setIcon(ButtonIcon2);
    QSize size1 = pixmap2.rect().size();
    size1.setHeight(size1.height() -10);
    size1.setWidth(size1.width() -10);
    ui->pushB_ZoomIn->setIconSize(size1);


    QPixmap pixmap3("actions/zoom-out-3.ico");
    QIcon ButtonIcon3(pixmap3);
    ui->pushB_ZoomOut->setIcon(ButtonIcon3);
    QSize size2 = pixmap3.rect().size();
    size2.setHeight(size2.height() -10);
    size2.setWidth(size2.width() -10);
    ui->pushB_ZoomOut->setIconSize(size2);



}


ImageWindows::~ImageWindows()
{
    //delete image_ihm;
    delete ui;
}

//Enregistrer le fichier sous
void ImageWindows::on_pushB_Save_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(ui->lbl_imageSize, "Ouvrir un fichier", QString(), "Images (*.bmp)");
    if(!fichier.isEmpty())
        image_ihm.save(fichier);
}

//Zoom --
void ImageWindows::on_pushB_ZoomOut_clicked()
{
    m_coeffZoom = m_coeffZoom/2;
    //m_coeffZoom = m_coeffZoom +2;
    affichageImage(image_ihm,m_coeffZoom,ui->scrollArea_Image);
}

//Zoom ++
void ImageWindows::on_pushB_ZoomIn_clicked()
{
    m_coeffZoom = m_coeffZoom*2;
    affichageImage(image_ihm,m_coeffZoom,ui->scrollArea_Image);
}

void ImageWindows::Mouse_current_pos()
{
    ui->lbl_x->setText(QString("X = %1, Y= %2").arg(imageLbl->x/m_coeffZoom).arg(imageLbl->y/m_coeffZoom));
    if(!image_ihm.isGrayscale()){

        /*ui->lbl_pixelvalue->setText(QString("R = %1 , G = %2 ,  B = %3")
                                    .arg(imageCouleur.operator ()(imageLbl->y/m_coeffZoom, imageLbl->x/m_coeffZoom)[0])
                                    .arg(imageCouleur.operator ()(imageLbl->y/m_coeffZoom, imageLbl->x/m_coeffZoom)[1])
                                    .arg(imageCouleur.operator ()(imageLbl->y/m_coeffZoom, imageLbl->x/m_coeffZoom)[2]));*/
        QRgb rgb = image_ihm.pixel(imageLbl->x/m_coeffZoom, imageLbl->y/m_coeffZoom);

        ui->lbl_pixelvalue->setText(QString("R = %1 , G = %2 ,  B = %3")
                                        .arg(qRed(rgb))
                                        .arg(qGreen(rgb))
                                        .arg(qBlue(rgb)));

    }else{

        QRgb rgb = image_ihm.pixel(imageLbl->x/m_coeffZoom, imageLbl->y/m_coeffZoom);

        ui->lbl_pixelvalue->setText(QString("NDG = %1")
                                        .arg(qRed(rgb)));

    }





}

void ImageWindows::Mouse_pressed()
{

}

void ImageWindows::MouseClickLeft()
{

}

void ImageWindows::Mouse_release_pos()
{
   // ui->lbl_y->setText(QString("X = %1, Y= %2").arg(imageLbl->xr).arg(imageLbl->yr));
}

void ImageWindows::affichageImage(QImage img, float k, QScrollArea *scroll)
{
    //imageLbl=new qlabel_image();
    imageLbl->setScaledContents(true);

    imageLbl->setFixedWidth(img.width()*k);
    imageLbl->setFixedHeight(img.height()*k);

    imageLbl->setPixmap(QPixmap::fromImage(expanssionAffichage(img)));
    scroll->setWidget(imageLbl);
}

QImage ImageWindows::getImageCurrent(){
    return image_ihm;
}

void ImageWindows::setImageCurrent(QImage im){
   // m_coeffZoom = 1;
    image_ihm = im;
    affichageImage(im,m_coeffZoom,ui->scrollArea_Image);

    if(image_ihm.isGrayscale())
        ui->lbl_imageDepth->setText("niveau de gris");
    else
        ui->lbl_imageDepth->setText("couleurs");
}



void ImageWindows::on_actionZoomPlus_triggered()
{
    qDebug() << "Action!"; // do what you want here
    on_pushB_ZoomIn_clicked();
}

void ImageWindows::on_actionZoomMoins_triggered()
{
    qDebug() << "Action!"; // do what you want here
    on_pushB_ZoomOut_clicked();
}

//Fonction permettant de faire lexpanssion de la dynamique de l'image a partir de la palette
QImage ImageWindows::expanssionAffichage(QImage img){

    QImage im_expand = img;

    if(!img.isGrayscale())
        return img;

    unsigned char valeur_max = 0;
    for(int i = 0; i< img.height(); i++){
        uchar * bits = im_expand.scanLine(i);
            for(int j = 0; j< img.width(); j++ ){
                if(valeur_max <  bits[j])
                    valeur_max = bits[j] ;
            }
    }
    if(valeur_max < 5){
        im_expand.setColor(0,qRgb(0, 0, 0) );
        im_expand.setColor(1,qRgb(255, 255, 255) );
    }

    return im_expand;
}

