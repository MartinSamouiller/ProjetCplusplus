#ifndef FILTRAGE_H
#define FILTRAGE_H

#include <QWidget>
#include <QMdiArea>
#include "imagewindows.h"
#include <QMdiSubWindow>

////Classe graphique permettant d'appliquer des filtrages sur des images ndg ou couleurs
/// NDG : moyennage et ecart type
/// Couleurs : taille et maxima locaux

namespace Ui {
class Filtrage;
}

class Filtrage : public QWidget
{
    Q_OBJECT

public:
    explicit Filtrage(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    explicit Filtrage(QWidget *parent = 0);
    ~Filtrage();

private slots:
    void on_bout_valider_clicked();
    void on_bout_annuler_clicked();

private:
    Ui::Filtrage *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
    ImageWindows *ImWin;
    QMdiSubWindow *subWindow1;
};

#endif // FILTRAGE_H
