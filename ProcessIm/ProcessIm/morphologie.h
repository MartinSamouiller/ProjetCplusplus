#ifndef MORPHOLOGIE_H
#define MORPHOLOGIE_H

#include <QWidget>
#include <QMdiArea>

////Classe graphique permettant d'appliquer des opérations de morphologies sur des images ndg


namespace Ui {
class Morphologie;
}

class Morphologie : public QWidget
{
    Q_OBJECT

public:
    explicit Morphologie(QWidget *parent = 0);
    explicit Morphologie(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    ~Morphologie();

private slots:
    void on_bout_valider_clicked();

private:
    Ui::Morphologie *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;

};

#endif // MORPHOLOGIE_H
