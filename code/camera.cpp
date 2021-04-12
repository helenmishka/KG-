#include "camera.h"

void fillVec(double v[4], Point p) {
    v[0] = p.x;
    v[1] = p.y;
    v[2] = p.z;
    v[3] = 1;
}

Camera::Camera(Size scSize) {
    m_scene = &(SingleScene::instance());

    connect(this, SIGNAL(getPoints(QVector<PointsToSend>&)), m_scene, SLOT(getPoints(QVector<PointsToSend>&)));
    connect(this, SIGNAL(getPolygons(QVector<QVector<PointsToSend> >&)), m_scene, SLOT(getPolygons(QVector<QVector<PointsToSend> >&)));

    m_sceneSize = scSize;
    m_scene->setSize(scSize);

    clearMatr();
}

void Camera::toHomePosition() {
    clearMatr();
}

void Camera::move(double dx, double dy, double dz) {
    double conv[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {dx, dy, dz, 1}
    };
    multMatr(convertionMatr, conv);
}

void Camera::rotateX(double angle) {
    double conv[4][4] = {
        {1, 0, 0, 0},
        {0, cos(angle), sin(angle), 0},
        {0, -sin(angle), cos(angle), 0},
        {0, 0, 0, 1}
    };
    multMatr(convertionMatr, conv);
}

void Camera::rotateY(double angle) {
    double conv[4][4] = {
        {cos(angle), 0, -sin(angle), 0},
        {0, 1, 0, 0},
        {sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}
    };
    multMatr(convertionMatr, conv);
}

void Camera::rotateZ(double angle) {
    double conv[4][4] = {
        {cos(angle), sin(angle), 0, 0},
        {-sin(angle), cos(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    multMatr(convertionMatr, conv);
}

void Camera::scale(double sx, double sy, double sz) {
    double conv[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    multMatr(convertionMatr, conv);
}

void Camera::convertion(Point& p) {
    double vec[4] = {
        p.x, p.y, p.z, 1
    };
    multVecMatr(vec, convertionMatr);
    p = Point(vec[0], vec[1], vec[2]);
}

void Camera::sendPoints(QVector<PointsToSend>& pv) {
    QVector<PointsToSend> pnts1;
    emit getPoints(pnts1);

    QVector<PointsToSend> pnts(pnts1);
    int cnt = pnts.count();
    for(int i = 0; i < cnt; ++i) 
		convertion(pnts[i].p);
    pv = pnts;
}

void Camera::sendPolygons(QVector<QVector<PointsToSend> > &pv) {
    QVector<QVector<PointsToSend> > pnts1;
    emit getPolygons(pnts1);

    QVector<QVector<PointsToSend> > pnts(pnts1);
    int cnt = pnts.count();
    for(int i = 0; i < cnt; ++i) {
        int cnt2 = pnts[i].count();
        for(int j = 0; j < cnt2; ++j)
            convertion(pnts[i][j].p);
    }
    pv = pnts;
}

void Camera::clearMatr() {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j)
            convertionMatr[i][j] = 0;
    }
    convertionMatr[0][0] = 1;
    convertionMatr[1][1] = 1;
    convertionMatr[2][2] = 1;
    convertionMatr[3][3] = 1;
}

void Camera::getCMatrix(double **&m) {
    staticToDynamic(m, convertionMatr);
}

CameraManager::CameraManager() {}

void CameraManager::createCamera() {
    Size s;
    getSize(s);
    m_cam = new Camera(s);
}

void CameraManager::removeCamera() {
    delete m_cam;
}


void CameraManager::sendPoints(QVector<PointsToSend>& pv) {
    m_cam->sendPoints(pv);
}

void CameraManager::move(int dx, int dy, int dz) {
    m_cam->move(dx, dy, dz);
}

void CameraManager::rotateX(double ang) {
    m_cam->rotateX(ang);
}

void CameraManager::rotateY(double ang) {
    m_cam->rotateY(ang);
}

void CameraManager::rotateZ(double ang) {
    m_cam->rotateZ(ang);
}

void CameraManager::scale(double sx, double sy, double sz) {
    m_cam->scale(sx, sy, sz);
}

void CameraManager::sendPolygons(QVector<QVector<PointsToSend> > &polvec) {
    m_cam->sendPolygons(polvec);
}
