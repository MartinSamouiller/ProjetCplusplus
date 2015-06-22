#ifndef COMPTAGE_H
#define COMPTAGE_H

#include <QWidget>
#include <QMdiArea>
#include "imagewindows.h"
#include <QMdiSubWindow>

////Classe graphique permettant de compter des objets sur une image NDG ou image couleurs

namespace Ui {
class Comptage;
}

class Comptage : public QWidget
{
    Q_OBJECT

public:
    explicit Comptage(QWidget *parent = 0);
    explicit Comptage(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    ~Comptage();

private slots:
    void on_BoutValider_clicked();

    void on_cbPlan_currentIndexChanged(const QString &arg1);

private:
    Ui::Comptage *ui;
    QImage im_courante;
    QImage im_transforme;
    QMdiArea * m_AreaMdi;
    ImageWindows *ImWin;
    QMdiSubWindow *subWindow1;
};

#endif // COMPTAGE_H
