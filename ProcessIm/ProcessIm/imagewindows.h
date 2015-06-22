#ifndef IMAGEWINDOWS_H
#define IMAGEWINDOWS_H

#include <QWidget>
#include <QScrollArea>
#include <QMouseEvent>
#include "qlabel_image.h"

////Classe graphique permettant d'afficher une image
/// chaque image dépend d'une IHM ImageWindows
/// cette classe permet la lecture x et y et RGB des pixels de l'image
/// permet également l'enregistrement et le zoom




namespace Ui {
class ImageWindows;
}

class ImageWindows : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWindows(QImage image, QString name, QWidget *parent = 0);
    explicit ImageWindows(QWidget *parent = 0);
    QString getImageName(){return m_StrImageName; };
    void affichageImage(QImage img, float k, QScrollArea *scroll);
    QImage getImageCurrent();
    QImage expanssionAffichage(QImage img);
    void setImageCurrent(QImage im);
    ~ImageWindows();

private slots:
    void on_pushB_Save_clicked();
    void on_pushB_ZoomOut_clicked();
    void on_pushB_ZoomIn_clicked();
    void Mouse_current_pos();
    void Mouse_pressed();
    void MouseClickLeft();
    void Mouse_release_pos();
    void on_actionZoomPlus_triggered();
    void on_actionZoomMoins_triggered();

private:
    Ui::ImageWindows *ui;
    QImage image_ihm;
    QString m_StrImageName;
    float m_coeffZoom;
    qlabel_image *imageLbl;

};

#endif // IMAGEWINDOWS_H
