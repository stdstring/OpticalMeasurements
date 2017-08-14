#pragma once

#include <QKeyEvent>
#include <QList>
#include <QOpenGLWidget>
#include <QWidget>

#include <memory>

#include "GL/gl.h"

#include "Vertex3D.h"


namespace OpenGLDemo
{

class OpenGLObjWidget : public QOpenGLWidget
{
public:
    OpenGLObjWidget(QWidget *parent = nullptr);
    ~OpenGLObjWidget();
    void ShowData(QList<Vertex3DData> const &dataList);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    bool _hasData;
    GLuint _dataDisplayList;
    double _rotationX;
    double _rotationY;
    double _shiftZ;
};

}
