#ifndef CONVERSION_H
#define CONVERSION_H

#include <QWidget>

#include <QMdiArea>

#include "imagewindows.h"
#include <QMdiSubWindow>

////Classe graphique permettant de convertir une image couleur en HSV (avec extraction des plan H,S,V ou R,G,B)

namespace Ui {
class Conversion;
}

class Conversion : public QWidget
{
    Q_OBJECT

public:
    explicit Conversion(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    explicit Conversion(QWidget *parent = 0);
    ~Conversion();

private slots:
    void on_radioButton_HSV_clicked();

    void on_radioButton_RGB_clicked();

    void on_pushButton_clicked();

private:
    void ConversionHSV();
    void CreerImageMdiArea(QImage image, QMdiArea * mdiArea, QString name_image);
    Ui::Conversion *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
};

#endif // CONVERSION_H
