#include "myglwidget.h"
#include <QOpenGLFunctions>
#include <QPainter>
#include <QCoreApplication>


MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {
    qDebug() << "dtor of MyGLWidget";
}

void MyGLWidget::initializeGL() {
    qDebug() << "initializeGL";

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    connect(qApp, &QCoreApplication::aboutToQuit, this, &MyGLWidget::cleanup);
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyGLWidget::cleanup);
}

void MyGLWidget::resizeGL(int w, int h) {
    qDebug() << "resizeGL";
}

void MyGLWidget::paintGL() {
    qDebug() << "paintGL";

    QPainter painter(this);
    painter.fillRect(0, 0, 128, 128, Qt::green);

    painter.beginNativePainting();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnable(GL_SCISSOR_TEST);
    f->glScissor(0, 0, 64, 64);
    f->glClearColor(1, 0, 0, 1);
    f->glClear(GL_COLOR_BUFFER_BIT);
    f->glDisable(GL_SCISSOR_TEST);

    painter.endNativePainting();
}

void MyGLWidget::cleanup()
{
    qDebug() << "clean up";

    disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyGLWidget::cleanup);

    makeCurrent();
    // more cleanup stuff if any
    doneCurrent();
}
