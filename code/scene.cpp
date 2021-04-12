#include "scene.h"

void Scene::getSceneSize(Size& p) {
    p = size;
}

void Scene::getPolygons(QVector<QVector<PointsToSend> > &p) {
    p = polygons;
}

void Scene::setPolygons(QVector<QVector<PointsToSend> > p) {
    polygons = p;
    foreach(QVector<PointsToSend> pnts, oXZ)
        polygons.push_back(pnts);
}

Scene* SingleScene::ptr = 0;

void fillSurface(QVector<QVector<PointsToSend> > &polvec, Size size) {
    QVector<PointsToSend> pnts;
    pnts.clear();
    Color areaCol = Color(255, 255, 255);
    PointsToSend pnt;
    pnt.p = Point(0, size.height, 0);
    pnt.c = areaCol;
    pnts.push_back(pnt);
    pnt.p.x = size.length;
    pnts.push_back(pnt);
    pnt.p.z = size.width;
    pnts.push_back(pnt);
    pnt.p.x = 0;
    pnts.push_back(pnt);
    polvec.push_back(pnts);

    for(int i = 0; i < 4; ++i) {
        ++pnts[i].p.y;
    }
    polvec.push_back(pnts);
    pnts.clear();

    pnt.p = Point(0, size.height, 0);
    pnts.push_back(pnt);
    pnt.p.x = size.length;
    pnts.push_back(pnt);
    pnt.p.y += 1;
    pnts.push_back(pnt);
    pnt.p.x = 0;
    pnts.push_back(pnt);
    polvec.push_back(pnts);

    for(int i = 0; i < 4; ++i) {
        pnts[i].p.z += size.width;
    }
    polvec.push_back(pnts);
    pnts.clear();

    pnt.p = Point(0, size.height, 0);
    pnts.push_back(pnt);
    pnt.p.z = size.width;
    pnts.push_back(pnt);
    pnt.p.y += 1;
    pnts.push_back(pnt);
    pnt.p.z = 0;
    pnts.push_back(pnt);
    polvec.push_back(pnts);

    for(int i = 0; i < 4; ++i) {
        pnts[i].p.x += size.length;
    }
    polvec.push_back(pnts);
    pnts.clear();
}

Scene::Scene(Size scSize) {
    size = scSize;

    fillSurface(oXZ, size);
}

void Scene::setSize(Size s) {
    size = s;

    fillSurface(oXZ, size);
}


Scene::Scene() {
    Size s(0, 0, 0);
    size = s;
}
