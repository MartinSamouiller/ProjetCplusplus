#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <QWidget>

#include <QMdiSubWindow>
#include <QMessageBox>
#include <QMdiArea>

////Classe graphique permettant d'extraite la signature des objets d'une image
/// cette classe gére également la création de la classe signatureform (permettant d'afficher un tableau de valeur)


namespace Ui {
class Signatures;
}

class Signatures : public QWidget
{
    Q_OBJECT

public:
    explicit Signatures(QWidget *parent = 0);
    explicit Signatures(QMdiArea *areaffichage, QImage im, QWidget *parent = 0);
    ~Signatures();

private slots:
    void on_pushButton_Valider_clicked();

private:
    Ui::Signatures *ui;
    QImage im_courante;
    QMdiArea * m_AreaMdi;
};

#endif // SIGNATURES_H
