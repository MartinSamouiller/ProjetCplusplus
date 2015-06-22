#ifndef FENETRETRAITEMENT_H
#define FENETRETRAITEMENT_H

#include <QDialog>

namespace Ui {
class FenetreTraitement;
}

class FenetreTraitement : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreTraitement(QWidget *parent = 0);
    ~FenetreTraitement();

private:
    Ui::FenetreTraitement *ui;
};

#endif // FENETRETRAITEMENT_H
