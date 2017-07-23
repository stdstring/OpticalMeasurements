#include <QKeyEvent>
#include <QOpenGLWidget>
#include <Qt>
#include <QWidget>

#include "GL/gl.h"
#include "GL/glu.h"

#include "OpenGLXYZWidget.h"

namespace OpenGLDemo
{

OpenGLXYZWidget::OpenGLXYZWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

void OpenGLXYZWidget::initializeGL()
{
}

void OpenGLXYZWidget::paintGL()
{
}

void OpenGLXYZWidget::resizeGL(int width, int height)
{
}

void OpenGLXYZWidget::keyPressEvent(QKeyEvent *event)
{
}

}
