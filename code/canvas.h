#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QtGui>
#include "user_definitions.h"

struct drawablePoint {
    QPoint pnt;
    QColor col;

    drawablePoint() {}
    drawablePoint(Point p, Color c) {
        pnt = QPoint(int(p.x), int(p.y));
        col = QColor(c.r, c.g, c.b, 255);
    }
};

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

    void setImage(QImage i) { *img = i; }

    Color background;
    
protected:
    virtual void resizeEvent(QResizeEvent *re);

    virtual void paintEvent(QPaintEvent *);
    virtual QSize sizeHint() const {
        return QSize(1000, 1000);
    }
    virtual QSizePolicy sizePolicy() {
        return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

public slots:
private:
    QImage *img;

};

#endif // CANVAS_H
