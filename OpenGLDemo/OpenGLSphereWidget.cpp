#include <QObject>
#include <QOpenGLWidget>
#include <Qt>
#include <QWidget>

#include "GL/gl.h"
#include "GL/glu.h"

#include "OpenGLSphereWidget.h"

namespace OpenGLDemo
{

namespace
{

GLfloat LightAmbient[]= {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[]= {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[]= {0.0f, 0.0f, 2.0f, 1.0f};

GLdouble RotationXDelta = 5;
GLdouble RotationYDelta = 5;
GLdouble ShiftZDelta = 0.2;

GLdouble Rotate(GLdouble angle, GLdouble delta)
{
    GLdouble newAngle = angle + delta;
    if (newAngle >= 360)
        return newAngle - 360;
    if (newAngle < 0)
        return 360 + newAngle;
    return newAngle;
}

}

OpenGLSphereWidget::OpenGLSphereWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    _rotationX(0),
    _rotationY(0),
    _shiftZ(-5.0)
{
}

void OpenGLSphereWidget::initializeGL()
{
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    _quadric = gluNewQuadric();
    gluQuadricNormals(_quadric, GLU_SMOOTH);
}

void OpenGLSphereWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // TODO (std_string) : think about problems with RGBA
    glColor3d(0.1875, 0.832, 0.7813);
    glLoadIdentity();
    glTranslated(0.0, 0.0, _shiftZ);
    glRotated(_rotationX, 1, 0, 0);
    glRotated(_rotationY, 0, 1, 0);
    glPushMatrix();
    glTranslated(1.0, 1.0, 0);
    gluSphere(_quadric, 0.2, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.0, -1.0, 0);
    gluSphere(_quadric, 0.2, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1.0, -1.0, 0);
    gluSphere(_quadric, 0.2, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1.0, 1.0, 0);
    gluSphere(_quadric, 0.2f, 32, 32);
    glPopMatrix();
}

void OpenGLSphereWidget::resizeGL(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble) width / (GLdouble) height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLSphereWidget::keyPressEvent(QKeyEvent *event)
{
    if (Qt::Key_Left == event->key())
    {
        _rotationY = Rotate(_rotationY, -RotationYDelta);
        repaint();
    }
    if (Qt::Key_Right == event->key())
    {
        _rotationY = Rotate(_rotationY, RotationYDelta);
        repaint();
    }
    if (Qt::Key_Up == event->key())
    {
        _rotationX = Rotate(_rotationX, RotationXDelta);
        repaint();
    }
    if (Qt::Key_Down == event->key())
    {
        _rotationX = Rotate(_rotationX, -RotationXDelta);
        repaint();
    }
    if (Qt::Key_Plus == event->key())
    {
        _shiftZ += ShiftZDelta;
        repaint();
    }
    if (Qt::Key_Minus == event->key())
    {
        _shiftZ -= ShiftZDelta;
        repaint();
    }
}

}
