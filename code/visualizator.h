#ifndef VISUALIZATOR_H
#define VISUALIZATOR_H

#include <QtGui>
#include "user_definitions.h"
#include "scene.h"

class AbstractVisualizator : public QObject {
    Q_OBJECT

public slots:
    virtual void Visualize(QImage &) = 0;

};

class ZBuffer : public AbstractVisualizator {
    Q_OBJECT

public:
    ZBuffer();
    ~ZBuffer();

    void initBuf(Cell ** &, int, int, Color);
    void clear();
    void draw();
    void pointsIntoBuffer(QVector<PointsToSend>, Cell ** &buff);
    void polygonsIntoBuffer(QVector<QVector<PointsToSend> >, Cell ** &);
    QVector<Triangle> divideToTriangles(QVector<PointsToSend>);
    void putTriangle(Triangle&, Cell ** &);

public slots:
    void Visualize(QImage &i) { i = *img; }
    void takeObjects(QVector<PointsToSend>, QVector<QVector<PointsToSend> >);

signals:
    void getSize(Size&);
    void getBackground(Color&);
    void getLightSourceConversation(double**&);
    void getConvMatr(double **&);

private:
    Cell** buff;
    QVector<QVector<PointsToSend> > originalPoints;
    QVector<Triangle> triangles;
    int sX, sY;
    double toLightSourcePos[4][4];
    QImage *img;
};

#endif // VISUALIZATOR_H
