#ifndef WIDGET_H
#define WIDGET_H

#include <gl/glew.h>

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <iostream>
#include "Shader.h"
#include <memory>

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
private:
    QOpenGLShaderProgram program;
	std::shared_ptr<Shader> m_shader;
};

#endif // WIDGET_H
