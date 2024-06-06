#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyGLWidget(QWidget * parent = nullptr);
    ~MyGLWidget();

    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    void cleanup();
};

#endif // MYGLWIDGET_H
