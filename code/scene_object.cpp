#include "scene_object.h"

House::House() {
    m_scene = &SingleScene::instance();
    location = Point(100, m_scene->getSize().height, 200);
    centerLoc = Point(100 + double(CUBE_SIZE)/2, location.y - double(CUBE_SIZE) - ROOF_HEIGHT, 200 - double(CUBE_SIZE)/2);
    col = Color(139, 69, 19);
    fundcol = Color(255,255,255);
    roofCol = Color(128, 128, 0);
    windowCol = Color(240, 235, 75);

    connect(this, SIGNAL(setHouseOnScene(QVector<QVector <PointsToSend> >)), m_scene, SLOT(setPolygons(QVector<QVector <PointsToSend> >)));

    facets << getFront1()
           << getFront2()
           << getFront3()
           << getFront4()
           << getFront5()
           << getLeft()
           << getBack()
           << getRight()
           << getRoof0()
           << getRoof1()
           << getRoof2()
           << getRoof3()
           << getRoof4()
           << getWindow1()
           << getWindow2();

    emit setHouseOnScene(facets);
}


QVector<PointsToSend> House::getFundament() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, fundcol);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z += double(CUBE_SIZE);
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getRoof0() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, roofCol);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z += double(CUBE_SIZE);
    plg.push_back(pnt);

    return plg;
}

QVector<PointsToSend> House::getRoof1() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, roofCol);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);;
    pnt.p = centerLoc;
    plg.push_back(pnt);;

    return plg;
}

QVector<PointsToSend> House::getRoof2() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, roofCol);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p = centerLoc;
    plg.push_back(pnt);

    return plg;
}

QVector<PointsToSend> House::getRoof3() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, roofCol);
    pnt.p.y -= double(CUBE_SIZE);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p = centerLoc;
    plg.push_back(pnt);

    return plg;
}

QVector<PointsToSend> House::getRoof4() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, roofCol);
    pnt.p.y -= double(CUBE_SIZE);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p = centerLoc;
    plg.push_back(pnt);

    return plg;
}

QVector<PointsToSend> House::getRight() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z += double(CUBE_SIZE);
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getLeft() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.z += double(CUBE_SIZE);
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getBack() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.z -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE);
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getFront1() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/3;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/3;
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getFront2() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.y -= double(CUBE_SIZE)/3;
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE)/10;
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getFront3() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.y -= double(CUBE_SIZE)/3;
    pnt.p.x += 13*double(CUBE_SIZE)/30;
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    pnt.p.x += 2*double(CUBE_SIZE)/15;
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getFront4() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.y -= double(CUBE_SIZE)/3;
    pnt.p.x += 9*double(CUBE_SIZE)/10;
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE)/10;
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getFront5() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, col);
    pnt.p.y -= 5*double(CUBE_SIZE)/6;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE);
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/6;
    plg.push_back(pnt);
    pnt.p.x -= double(CUBE_SIZE);
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getWindow1() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, windowCol);
    pnt.p.y -= double(CUBE_SIZE)/3;
    pnt.p.x += double(CUBE_SIZE)/10;
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE)/3;
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    return plg;
}

QVector<PointsToSend> House::getWindow2() {
    QVector<PointsToSend> plg;
    PointsToSend pnt(location, windowCol);
    pnt.p.y -= double(CUBE_SIZE)/3;
    pnt.p.x += 17*double(CUBE_SIZE)/30;
    plg.push_back(pnt);
    pnt.p.y -= double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    pnt.p.x += double(CUBE_SIZE)/3;
    plg.push_back(pnt);
    pnt.p.y += double(CUBE_SIZE)/2;
    plg.push_back(pnt);
    return plg;
}

