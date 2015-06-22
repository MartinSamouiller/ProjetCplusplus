#include "infowindows.h"
#include "ui_infowindows.h"


InfoWindows::InfoWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWindows)
{
    ui->setupUi(this);
    QString path = QApplication::applicationDirPath () + "/Image/im0002.jpg" ;
    QImage image(path);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

InfoWindows::~InfoWindows()
{
    delete ui;
}

void InfoWindows::on_pushButton_clicked()
{
    close();
}
