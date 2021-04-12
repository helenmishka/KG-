#include "visualizator.h"
#include <iostream>

void ZBuffer::initBuf(Cell ** &b, int y, int x, Color c) {
    if(x != sX || y != sY) {
        b = (Cell**)malloc(y*sizeof(Cell*));
        for(int i = 0; i < y; i++) {
            b[i] = (Cell*)malloc(x*sizeof(Cell));
        }
        sX = x;
        sY = y;
    }

    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            b[i][j].z = MIN_Z;
            b[i][j].col = c;
        }
    }
}

ZBuffer::ZBuffer() {
    Size scSize;
    emit getSize(scSize);

    sX = scSize.length;
    sY = scSize.height;

    initBuf(buff, sY, sX, Color());;
    img = new QImage(sX, sY, QImage::Format_ARGB32_Premultiplied);

}

ZBuffer::~ZBuffer() {
    delete img;
    for(int i = 0; i < sY; ++i) {
        delete buff[i];
    }
    delete buff;
    delete img;
}

void ZBuffer::clear() {
    QPainter p(img);
    p.eraseRect(-1, -1, sX, sY);
}

void ZBuffer::draw() {
    QColor qc;
    for(int i = 0; i < sY; ++i) {
        for(int j = 0; j < sX; ++j) {
            qc = buff[i][j].col.toQColor();
            img->setPixel(QPoint(j, i), qc.rgba());
        }
    }
}


void ZBuffer::pointsIntoBuffer(QVector<PointsToSend> pnts, Cell ** &buff) {
    foreach(PointsToSend pnt, pnts) {
        int i(round(pnt.p.y)), j(round(pnt.p.x));
        if(i < 0 || i >= sY || j < 0 || j >= sX) continue;
        double z = pnt.p.z;
        if(z > buff[i][j].z) {
            buff[i][j].z = z;
            buff[i][j].col = pnt.c;
        }
    }
}

void ZBuffer::polygonsIntoBuffer(QVector<QVector<PointsToSend> > plgs, Cell ** &buff) {
    QVector<Triangle> tvec;
    triangles.clear();
    foreach(QVector<PointsToSend> plg, plgs) {
        tvec = divideToTriangles(plg);
        foreach(Triangle t, tvec)
            triangles.push_back(t);
    }

    foreach(Triangle t, triangles)
        putTriangle(t, buff);
}

QVector<Triangle> ZBuffer::divideToTriangles(QVector<PointsToSend> plg) {
    QVector<Triangle> trs;
    Color col(plg[0].c);
    int cnt(plg.count());

    for(int i = 2; i < cnt; ++i) {
        trs.push_back(Triangle(plg[0].p, plg[i-1].p, plg[i].p, col));
    }

    return trs;
}

void ZBuffer::takeObjects(QVector<PointsToSend> pnts, QVector<QVector<PointsToSend> > plgs) {
    Size scSize;
    Color back;
    emit getSize(scSize);
    emit getBackground(back);

    initBuf(buff, scSize.height, scSize.length, back);
    delete img;
    img = new QImage(QSize(sX, sY), QImage::Format_ARGB32_Premultiplied);

    pointsIntoBuffer(pnts, buff);
    polygonsIntoBuffer(plgs, buff);

    draw();
}


void ZBuffer::putTriangle(Triangle &t, Cell ** &buff) {
    int ymax, ymin;
    int x[3], y[3];

    for(int i = 0; i < 3; ++i) {
        x[i] = int(t.p[i].x);
        y[i] = int(t.p[i].y);
    }

    ymax = ymin = y[0];
    if(ymax < y[1])
        ymax = y[1];
    else
        if(ymin > y[1])
            ymin = y[1];

    if(ymax < y[2])
        ymax = y[2];
    else
        if(ymin > y[2])
            ymin = y[2];

    if(ymin < 0)
        ymin = 0;
    if(ymax > sY)
        ymax = sY;

    int x1, x2;
    double z1, z2;

    for (int ysc = ymin; ysc < ymax; ++ysc) {
        int ne = 0;
        for(int e = 0; e < 3; ++e) {
            int e1= e + 1;
            if(e1 == 3) e1 = 0;
            if(y[e] < y[e1]) {
                if(y[e1] <= ysc || ysc < y[e]) continue;
            }
            else
                if(y[e] > y[e1]) {
                    if(y[e1] > ysc || ysc >= y[e]) continue;
            } else continue;

            double tc = double(y[e] - ysc) / (y[e] - y[e1]);
            if(ne) {
                x2 = x[e] + int(tc * (x[e1] - x[e]));
                z2 = t.p[e].z + tc * (t.p[e1].z - t.p[e].z);
            } else {
                x1 = x[e] + int(tc * (x[e1] - x[e]));
                z1 = t.p[e].z + tc * (t.p[e1].z - t.p[e].z);
            }
            ne = 1;
        }
        if(x2 < x1) {
            int e = x1;
            x1 = x2;
            x2 = e;
            double tc = z1;
            z1 = z2;
            z2 = tc;
        }

        int xsc1 = (x1 < 0) ? 0 : x1;
        int xsc2 =(x2 < sX) ? x2 : sX;
        for (int xsc = xsc1; xsc <= xsc2; ++xsc) {
            double tc = double(x1 - xsc) / (x1 - x2);
            double z = z1 + tc * (z2 - z1);

            if (z > (*( buff[ysc] + xsc )).z)
                (*(buff[ysc] + xsc)).col = t.col,
                (*(buff[ysc] + xsc)).z = z;
            }
    }
}
























