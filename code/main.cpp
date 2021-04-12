#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#include "camera.h"
#include "particle_system.h"
#include "scene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnowModeling rsm;
    rsm.show();
    
    return a.exec();
}
