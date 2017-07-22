#pragma once

#include <QObject>
#include <QOpenGLWidget>
#include <QWidget>

#include "GL/gl.h"
#include "GL/glu.h"

namespace OpenGLDemo
{

class OpenGLSphereWidget : public QOpenGLWidget
{
public:
    explicit OpenGLSphereWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height);

private:
    GLUquadricObj *_quadric;
};

}
