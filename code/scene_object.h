#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#define __DEBUG_RT
#define CUBE_SIZE 200
#define ROOF_HEIGHT 60
#define SURFACE 200

#include "scene.h"
#include "user_definitions.h"

#include <QObject>
#include <QVector>
#include <QPolygon>

class House : public QObject {
    Q_OBJECT

public:
    House();
    ~House() {  }
    QVector<PointsToSend> getRoof0();
    QVector<PointsToSend> getRoof1();
    QVector<PointsToSend> getRoof2();
    QVector<PointsToSend> getRoof3();
    QVector<PointsToSend> getRoof4();
    QVector<PointsToSend> getFundament();
    QVector<PointsToSend> getRight();
    QVector<PointsToSend> getLeft();
    QVector<PointsToSend> getBack();
    QVector<PointsToSend> getFront1();
    QVector<PointsToSend> getFront2();
    QVector<PointsToSend> getFront3();
    QVector<PointsToSend> getFront4();
    QVector<PointsToSend> getFront5();
    QVector<PointsToSend> getWindow1();
    QVector<PointsToSend> getWindow2();


signals:
    void setHouseOnScene(QVector<QVector <PointsToSend> >);

private:
    Point location, centerLoc; // первая точка первой грани (дом должен стоять на земле)
    QVector<QVector <PointsToSend> > facets;
    Scene *m_scene;
    Color col, roofCol, windowCol,fundcol ;
};

#endif // SCENE_OBJECT_H
