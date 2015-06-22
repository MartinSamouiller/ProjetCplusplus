#ifndef LECTURECB_H
#define LECTURECB_H

#include <QWidget>
#include <QMdiArea>

////Classe graphique permettant de lire un code barre de type 128
/// PAS ENCORE FONCTIONNELLE SUR Qt

namespace Ui {
class LectureCB;
}

class LectureCB : public QWidget
{
    Q_OBJECT

public:
    explicit LectureCB(QWidget *parent = 0);
    explicit LectureCB(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    ~LectureCB();

private slots:
    void on_BoutValider_clicked();

private:
    Ui::LectureCB *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
};

#endif // LECTURECB_H
