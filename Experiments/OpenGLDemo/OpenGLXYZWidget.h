#pragma once

#include <QKeyEvent>
#include <QList>
#include <QOpenGLWidget>
#include <QWidget>

#include <memory>

#include "GL/gl.h"
#include "GL/glu.h"

#include "Vertex3D.h"

namespace OpenGLDemo
{

class OpenGLXYZWidget : public QOpenGLWidget
{
public:
    OpenGLXYZWidget(QWidget *parent = nullptr);
    ~OpenGLXYZWidget();
    void ShowData(QList<Vertex3D> const &vertexList);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    bool _hasData;
    GLUquadricObj *_quadric;
    GLuint _dataDisplayList;
    double _rotationX;
    double _rotationY;
    double _shiftZ;
};

}
