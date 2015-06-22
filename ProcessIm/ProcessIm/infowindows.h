#ifndef INFOWINDOWS_H
#define INFOWINDOWS_H

#include <QWidget>


////Page de démarrage de l'application


namespace Ui {
class InfoWindows;
}

class InfoWindows : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWindows(QWidget *parent = 0);
    ~InfoWindows();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InfoWindows *ui;
};

#endif // INFOWINDOWS_H
