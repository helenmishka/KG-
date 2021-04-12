#include "particle_system.h"

double randDbl() {
    return rand() / ((double)RAND_MAX + 1.0);
}


ParticleSystem::ParticleSystem(Size sceneSize, Intensity i) {
    m_sceneSize = sceneSize;
    intens = i;
    connect(this, SIGNAL(setPoints(QVector<PointsToSend>)), &(SingleScene::instance()), SLOT(setPoints(QVector<PointsToSend>)));
}

void ParticleSystem::moveParticle(Particle& p) {
    p.incLifetime();
    p.incLocation();
    p.incVelocity();
}


void Snow::moveParticles() {
    int cnt = snowflakes.count();
    for(int i = 0; i < cnt; ++i) {
        moveParticle(snowflakes[i]);
        if(snowflakes[i].getLifetime() > maxLifetime ||
                snowflakes[i].getLocation().y > m_sceneSize.height) {
            snowflakes.removeAt(i);
            --cnt;
        }
    }
}

int ParticleSystem::getParticleNumber() {
    int maxCount = (m_sceneSize.length + m_sceneSize.height + m_sceneSize.width);
    return int(double(maxCount) * 0.01 * double(intens*intens*intens));
}

void Snow::generateParticle() {
    SnowPart& particle = createParticle();
    makeParticleCharacter(particle);
    snowflakes.push_back(particle);
}

void ParticleSystem::generateParticles() {
    int n = getParticleNumber();
    y_beg = -3;
    for(int i = 0; i < n; ++i) {
        generateParticle();
    }
}

void ParticleSystem::setIntensity(Intensity i) {
    intens = i;
}

void ParticleSystem::makeParticleCharacter(Particle &particle) {
    Point loc;
    loc.x = m_sceneSize.length * randDbl();
    loc.y = y_beg;
    loc.z = m_sceneSize.width*randDbl();
    particle.setLocation(loc);
    particle.setLifetime(0);
    Color col;
    col.r = avrColor.r + int(2.0*(randDbl()*2 - 1));
    col.g = avrColor.g + int(2.0*(randDbl()*2 - 1));
    col.b = avrColor.b + int(2.0*(randDbl()*2 - 1));
    particle.setColor(col);
    particle.setVelocity(avrVelocity + 5*(randDbl()*2 - 1));
}


void Snow::sendToScene() {
    QVector<PointsToSend> pnts;
    foreach(SnowPart p, snowflakes) {
        pnts.push_back(PointsToSend(p.getLocation(), p.getColor()));
    }
    emit setPoints(pnts);
}
Snow::Snow(Size s, Intensity i): ParticleSystem(s, i) {
    avrVelocity = 10;
    avrColor = Color(250, 250, 250);
    maxLifetime = 1000;
}

SnowPart &Snow::createParticle() {
    return *(new SnowPart());
}


PSManager::PSManager() : m_ps(NULL) {}


void PSManager::createSnow() {
    Size s;
    Intensity intens;
    emit getSize(s);

    emit getIntensity(intens);

    delete m_ps;
    m_ps = new Snow(s, intens);
}

void PSManager::tickAction() {
    m_ps->moveParticles();
    m_ps->generateParticles();
}

void PSManager::generateNewParticles() {
    m_ps->generateParticles();
}
