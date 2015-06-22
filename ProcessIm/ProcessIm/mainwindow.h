#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>

////Page principale de l'application
/// Permet d'acceder a tous les traitements
/// La Mdi Area permet d'afficher les IHM qui contiennent les Images à traiter



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_actionOuvrir_une_image_triggered();
    void on_actionQuitter_triggered();
    void on_actionTutoriel_triggered();
    void on_actionA_propos_de_ProcessIm_triggered();
    void on_actionDossier_de_travail_triggered();
    void on_cbTraitement_currentIndexChanged(const QString &arg1);
    void on_cbAnalyse_currentIndexChanged(const QString &arg1);

    void on_actionDistance_au_fond_triggered();

    void on_actionFiltrage_triggered();

    void on_actionSeuillage_triggered();

    void on_actionMorphologie_triggered();

    void on_actionTransformation_triggered();

    void on_actionHistogramme_triggered();

    void on_actionConversion_triggered();

    void on_actionLecture_codes_barres_triggered();

    void on_actionSignatures_triggered();

    void on_actionComptage_objet_triggered();

signals:
    void SelectImage();

private:
    Ui::MainWindow *ui;
    QImage *image_courante;
    std::vector<QImage> images;
    int m_index_image = 0;
    //QBoxLayout *Layout_Travail;


};

#endif // MAINWINDOW_H
