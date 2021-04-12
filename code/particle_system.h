#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <QtGui>
#include "user_definitions.h"
#include "particle.h"
#include "scene.h"

double randDbl();

class ParticleSystem : public QObject {
    Q_OBJECT

public:
    ParticleSystem(Size, Intensity = DISAPPEAR);

    virtual ~ParticleSystem() {}

    virtual void moveParticles() {}
    void moveParticle(Particle&);
    int getParticleNumber();
    virtual void generateParticle() {}
    void generateParticles();
    virtual void sendToScene() {}
    void setIntensity(Intensity i);

protected:
    void makeParticleCharacter(Particle&);
    double avrVelocity;
    Color avrColor;
    int maxLifetime;
    Intensity intens;

    Size m_sceneSize;
    int y_beg;

signals:
    void setPoints(QVector<PointsToSend> pvec);
};

class Snow : public ParticleSystem {
    Q_OBJECT

public:
    Snow(Size s, Intensity = DISAPPEAR);
    ~Snow() { snowflakes.clear(); }
    void generateParticle();
    void moveParticles();
    void sendToScene();

protected:
    SnowPart& createParticle();

private:
    QList<SnowPart> snowflakes;
};


class PSManager : public QObject {
    Q_OBJECT

public:
    PSManager();
    ~PSManager() {
        delete m_ps;
    }
    void createSnow();
    void sendToScene() { m_ps->sendToScene(); }
    void tickAction();

public slots:
    void generateNewParticles();
    void setIntensity(Intensity i) { m_ps->setIntensity(i); }

signals:
    void getSize(Size&);
    void getIntensity(Intensity&);

private:
    ParticleSystem *m_ps;
};


#endif // PARTICLE_SYSTEM_H
