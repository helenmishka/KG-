#ifndef CAMERA_H
#define CAMERA_H

#include <QtGui>
#include "user_definitions.h"
#include "calculations.h"
#include "scene.h"

#include <QVector>

class Camera: public QObject {
    Q_OBJECT

public:
    Camera(Size scSize);
    
	~Camera() {
        delete m_scene;
    }

    void toHomePosition();
    void move(double dx, double dy, double dz);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    void scale(double sx, double sy, double sz);

    void convertion(Point&);
    void sendPoints(QVector<PointsToSend>& pv);
    void sendPolygons(QVector<QVector <PointsToSend> >& pv);
    void clearMatr();
    void getCMatrix(double **&);

signals:
    void getPoints(QVector<PointsToSend>&);
    void getPolygons(QVector<QVector <PointsToSend> >&);

private:
    Scene *m_scene;
    Size m_sceneSize;
    double convertionMatr[4][4];
};

class CameraManager : public QObject {
    Q_OBJECT

public:
    CameraManager();
    ~CameraManager() {
        removeCamera();
    }

    void createCamera();
    void removeCamera();
    void sendPoints();

public slots:
    void move(int, int, int);
    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void scale(double, double, double);
    void toHome() { m_cam->toHomePosition(); }
    void sendPoints(QVector<PointsToSend>&);
    void sendPolygons(QVector<QVector <PointsToSend> >&);
    void getCMatrix(double **&m) { m_cam->getCMatrix(m); }

signals:
    void getSize(Size&);

private:
    Camera *m_cam;
};

#endif // CAMERA_H
