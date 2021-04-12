#include "canvas.h"
#include <iostream>

Canvas::Canvas(QWidget *pwgt) : QWidget(pwgt), img(NULL) {
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    background = Color(200, 200, 200);
}

void Canvas::resizeEvent(QResizeEvent *re) {
    QWidget::resizeEvent(re);
    if(img) delete img;
    img = new QImage(size(), QImage::Format_ARGB32_Premultiplied);
}

void Canvas::paintEvent(QPaintEvent *) {

    QPainter p(this);
    if(img)
    {
        p.drawImage(0,0, *img);
    }
}
