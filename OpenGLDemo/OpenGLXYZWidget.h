#pragma once

#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QWidget>

#include "GL/gl.h"
#include "GL/glu.h"


namespace OpenGLDemo
{

class OpenGLXYZWidget : public QOpenGLWidget
{
public:
    OpenGLXYZWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};

}
