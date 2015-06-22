#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QWidget>
#include <QMdiArea>

////Classe graphique permettant d'appliquer des transformations sur une image ndg
/// transformations : complement, expanssion, égalisation


namespace Ui {
class Transformation;
}

class Transformation : public QWidget
{
    Q_OBJECT

public:
    explicit Transformation(QWidget *parent = 0);
    explicit Transformation(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    ~Transformation();

private slots:
    void on_bout_valider_clicked();
    void on_bout_annuler_clicked();

    void on_cb_transformation_currentIndexChanged(const QString &arg1);

private:
    Ui::Transformation *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
};

#endif // TRANSFORMATION_H
