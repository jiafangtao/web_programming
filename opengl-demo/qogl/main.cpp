//#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include "myglwidget.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    MyGLWidget w;
    w.show();

    return a.exec();
}
