#include <QObject>
#include <QOpenGLWidget>
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

}

OpenGLSphereWidget::OpenGLSphereWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

void OpenGLSphereWidget::initializeGL()
{
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_SMOOTH);
    glClearColor(1, 1, 1, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    _quadric = gluNewQuadric();
    gluQuadricNormals(_quadric, GLU_SMOOTH);
}

void OpenGLSphereWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(0.2, 0.3, 0.4);
    gluSphere(_quadric, 0.5f, 32, 32);
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
    gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

}
