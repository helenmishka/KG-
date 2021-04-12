#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "camera.h"
#include "particle_system.h"
#include "scene_object.h"
#include "visualizator.h"
#include "user_definitions.h"
//#include "calculations.h"

namespace Ui {
class SnowModeling;
}

class SnowModeling : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SnowModeling(QWidget *parent = 0);
    ~SnowModeling();
    void sendPoints();
    void setSnowLabels();

protected:
    virtual void timerEvent(QTimerEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    
private slots:
    void on_rbtnSnow_clicked();
    void getSize(Size&);
    void getBackground(Color&);
    void getIntensity(Intensity&);
    void on_hsldIntensity_valueChanged(int value);

    void on_gbxIntensity_clicked();

    void on_lblHard_linkActivated(const QString &link);

signals:
    void getPoints(QVector<PointsToSend>&);
    void getPolygons(QVector<QVector <PointsToSend> >&);
    void generateNewParticles();
    void setIntensity(Intensity);
    void move(int, int, int);
    void toHome();
    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void scale(double, double, double);
    void sendObjects(QVector<PointsToSend>, QVector<QVector<PointsToSend> >);
    void getImage(QImage &);
    void setImage(QImage);
    void getCMatrix(double **&);

private:
    QBasicTimer *tmr;

    Ui::SnowModeling *ui;
    CameraManager *c_M;
    PSManager *ps_M;
    ZBuffer *zb;

    House *m_house;

    QImage img;
    double time;
    int tickCnt;
};

#endif // MAINWINDOW_H
