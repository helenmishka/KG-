#ifndef SCENE_H
#define SCENE_H

#include "user_definitions.h"
#include "particle_system.h"

class Scene : public QObject {
    Q_OBJECT

public:
    Scene();
    Scene(Size scSize);
    ~Scene() {}
    void setSize(Size s);
    Size getSize() const { return size; }

public slots:
    void getSceneSize(Size&);
    void getPoints(QVector<PointsToSend> &pvec) { pvec = pnts; }
    void getPolygons(QVector<QVector <PointsToSend> >& p);
    void setPoints(QVector<PointsToSend> pvec)  { pnts = pvec; }
    void setPolygons(QVector<QVector <PointsToSend> >);

private:
    Size size; // размерs осей х, y и z в локальных координатах

    QVector<PointsToSend> pnts;
    QVector<QVector <PointsToSend> > polygons;
    QVector<QVector<PointsToSend> > oXZ;

};

class SingleScene {
public:
    static Scene& instance() {
        return ptr ? *ptr : *(ptr = new Scene());
    }

protected:
    SingleScene() {}

private:
    static Scene *ptr;
    SingleScene(SingleScene const &);
    SingleScene & operator =(SingleScene const &);
};

#endif // SCENE_H
