#ifndef SEUILLAGE_H
#define SEUILLAGE_H

#include <QWidget>
#include <QMdiArea>

#include "imagewindows.h"
#include <QMdiSubWindow>

////Classe graphique permettant de seuiller une image ndg en dynamique
/// seuillage automatique / seuillage manuel

namespace Ui {
class Seuillage;
}

class Seuillage : public QWidget
{
    Q_OBJECT

public:
    explicit Seuillage(QWidget *parent = 0);
    explicit Seuillage(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    void CreerImageMdiArea(QImage image, QMdiArea * mdiArea, QString name_image);
    ~Seuillage();

private slots:



    void on_hs_bas_valueChanged(int value);

    void on_hs_haut_valueChanged(int value);

    void on_boutValider_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Seuillage *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
    ImageWindows *ImWin;
    QMdiSubWindow *subWindow1;
    bool isSeuillagePossible;
};

#endif // SEUILLAGE_H
