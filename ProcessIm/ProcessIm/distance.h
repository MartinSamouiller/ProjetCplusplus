#ifndef DISTANCE_H
#define DISTANCE_H

#include <QWidget>
#include <QMdiArea>

////Classe graphique permettant de calculer la distance au fond d'objets seuillés sur une image

namespace Ui {
class Distance;
}

class Distance : public QWidget
{
    Q_OBJECT

public:
    explicit Distance(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    explicit Distance(QWidget *parent = 0);
    void CreerImageMdiArea(QImage image, QMdiArea * mdiArea, QString name_image);
    ~Distance();

private slots:
    void on_boutValider_clicked();

private:
    Ui::Distance *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
};

#endif // DISTANCE_H
