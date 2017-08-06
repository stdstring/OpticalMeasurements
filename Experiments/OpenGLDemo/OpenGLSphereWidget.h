#pragma once

#include <QKeyEvent>
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
    virtual void resizeGL(int width, int height) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    GLUquadricObj *_quadric;
    GLuint _displayList;
    double _rotationX;
    double _rotationY;
    double _shiftZ;
};

}
