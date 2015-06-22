#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <QWidget>
#include <QGraphicsView>

////Classe graphique permettant d'afficher l'histogramme d'une image ndg ou couleur
/// NDG : 1 plan
/// Couleurs : 3plans


namespace Ui {
class Histogramme;
}

class Histogramme : public QWidget
{
    Q_OBJECT

public:
    explicit Histogramme(QImage im, QWidget *parent = 0);
    explicit Histogramme(QWidget *parent = 0);
    ~Histogramme();

private slots:
    void on_boutValider_clicked();

private:
    Ui::Histogramme *ui;
    QImage im_courante;
    QImage im_transforme;
    QGraphicsView * m_GraphicsView;
    QGraphicsScene *m_scene;
    QGraphicsRectItem *m_rectangle;
    QGraphicsLineItem *m_lines;

};

#endif // HISTOGRAMME_H
