#ifndef SIGNATUREFORM_H
#define SIGNATUREFORM_H

#include <QWidget>
#include "ImageClasse.h"

////Classe graphique permettant d'afficher le tableau des valeurs de signatures formes
/// Taille / surface / position / code freeman / rectangle englobant / centre de gravité


namespace Ui {
class SignatureForm;
}

class SignatureForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignatureForm(std::vector<SIGNATURE_Forme> sign, QWidget *parent = 0);
    explicit SignatureForm(QWidget *parent = 0);


    ~SignatureForm();

private:
    Ui::SignatureForm *ui;
};

#endif // SIGNATUREFORM_H
