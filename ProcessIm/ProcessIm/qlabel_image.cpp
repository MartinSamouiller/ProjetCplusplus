#include "qlabel_image.h"

qlabel_image::qlabel_image(QWidget *parent) :
    QLabel(parent)
{

}

qlabel_image::~qlabel_image()
{

}

void qlabel_image::mouseMoveEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit Mouse_Pos();
}

void qlabel_image::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void qlabel_image::leaveEvent(QEvent *)
{
    emit Mouse_ClickLeft();
}

void qlabel_image::mouseReleaseEvent(QMouseEvent *ev)
{
    this->xr = ev->x();
    this->yr = ev->y();
    emit Mouse_ReleasePos();
}

