#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QElapsedTimer>

SnowModeling::SnowModeling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnowModeling) {
    ui->setupUi(this);


    ui->m_canv->background = Color(37, 40, 80);
    setSnowLabels();

    c_M = new CameraManager();
    ps_M = new PSManager();
    zb = new ZBuffer();

    connect(c_M, SIGNAL(getSize(Size&)), this, SLOT(getSize(Size&)));

    connect(this, SIGNAL(move(int,int,int)), c_M, SLOT(move(int, int, int)));
    connect(this, SIGNAL(rotateX(double)), c_M, SLOT(rotateX(double)));
    connect(this, SIGNAL(rotateY(double)), c_M, SLOT(rotateY(double)));
    connect(this, SIGNAL(rotateZ(double)), c_M, SLOT(rotateZ(double)));
    connect(this, SIGNAL(scale(double,double,double)), c_M, SLOT(scale(double,double,double)));
    connect(this, SIGNAL(toHome()), c_M, SLOT(toHome()));
    connect(this, SIGNAL(getPoints(QVector<PointsToSend>&)), c_M, SLOT(sendPoints(QVector<PointsToSend>&)));
    connect(this, SIGNAL(getPolygons(QVector<QVector <PointsToSend> >&)), c_M, SLOT(sendPolygons(QVector<QVector <PointsToSend> >&)));
    connect(this, SIGNAL(getCMatrix(double**&)), c_M, SLOT(getCMatrix(double**&)));

    connect(zb, SIGNAL(getSize(Size&)), this, SLOT(getSize(Size&)));
    connect(zb, SIGNAL(getBackground(Color&)), this, SLOT(getBackground(Color&)));
    connect(this, SIGNAL(getImage(QImage&)), zb, SLOT(Visualize(QImage&)));
    connect(this, SIGNAL(sendObjects(QVector<PointsToSend>, QVector<QVector<PointsToSend> >)),
            zb, SLOT(takeObjects(QVector<PointsToSend>, QVector<QVector<PointsToSend> >)));

    connect(ps_M, SIGNAL(getSize(Size&)), this, SLOT(getSize(Size&)));
    connect(ps_M, SIGNAL(getIntensity(Intensity&)), this, SLOT(getIntensity(Intensity&)));

    connect(this, SIGNAL(generateNewParticles()), ps_M, SLOT(generateNewParticles()));
    connect(this, SIGNAL(setIntensity(Intensity)), ps_M, SLOT(setIntensity(Intensity)));

    c_M->createCamera();
    ps_M->createSnow();

    m_house = new House();

    tmr = new QBasicTimer();
    time = 0;
    tickCnt = 0;
    tmr->start(41, this);

}

SnowModeling::~SnowModeling() {
    delete ui;
    delete c_M;
    delete ps_M;
    delete m_house;
}

void SnowModeling::sendPoints() {
    QVector<PointsToSend> pnts;
    QVector<QVector<PointsToSend> > plgs;
    emit getPoints(pnts);
    emit getPolygons(plgs);

    emit sendObjects(pnts, plgs);
}

void SnowModeling::setSnowLabels() {
    ui->lblNothing->setText(tr("Осадков нет"));
    ui->lblNothing->setToolTip(tr(""));
    ui->lblMin->setText(tr("Слабый снегопад"));
    ui->lblMin->setToolTip(tr("Интенсивность не превышает 0,1 мм/ч"));
    ui->lblMiddle->setText("Средний снегопад");
    ui->lblMiddle->setToolTip(tr("Интенсивность 0,1-1 мм/ч"));
    ui->lblHard->setText(tr("Сильный снегопад"));
    ui->lblHard->setToolTip(tr("Интенсивность больше 1 мм/ч"));
    ui->lblMax->setText(tr("Очень сильный"));
    ui->lblMax->setToolTip(tr("Интенсивность может превышать 1,6 мм/ч"));
}

void SnowModeling::timerEvent(QTimerEvent *) {
    ps_M->tickAction();
    ps_M->sendToScene();

    sendPoints();

    emit getImage(img);
    ui->m_canv->setImage(img);
    ui->m_canv->repaint();
}

void SnowModeling::keyPressEvent(QKeyEvent *kpe) {
    switch(kpe->key()) {
    case Qt::Key_Home:
        emit toHome();
        break;
    case Qt::Key_Left:
        emit move(-MOVE, 0 ,0);
        break;
    case Qt::Key_Right:
        emit move(MOVE, 0, 0);
        break;
    case Qt::Key_Up:
        emit move(0, -MOVE ,0);
        break;
    case Qt::Key_Down:
        emit move(0, MOVE, 0);
        break;
    case Qt::Key_8:
        emit rotateX(ANGLE);
        break;
    case Qt::Key_4:
        emit rotateY(-ANGLE);
        break;
    case Qt::Key_6:
        emit rotateY(ANGLE);
        break;
    case Qt::Key_2:
        emit rotateX(-ANGLE);
        break;
    case Qt::Key_Plus:
        emit scale(SCALE, SCALE, SCALE);
        break;
    case Qt::Key_Minus:
        emit scale(1/SCALE, 1/SCALE, 1/SCALE);
        break;
    default: break;
    }
}

void SnowModeling::getSize(Size &s) {
    s.length = ui->m_canv->width();
    s.height = ui->m_canv->height();
    s.width = s.length;
}

void SnowModeling::getBackground(Color &col) {
    col = ui->m_canv->background;
}

void SnowModeling::getIntensity(Intensity &i) {
    i = Intensity(ui->hsldIntensity->sliderPosition());
}

void SnowModeling::on_hsldIntensity_valueChanged(int value) {
    emit setIntensity(Intensity(value));
    ui->m_canv->setFocus();
}
