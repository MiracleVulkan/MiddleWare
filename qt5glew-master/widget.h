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

	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    QOpenGLShaderProgram program;
	std::shared_ptr<Shader> m_shader;
	GLuint m_texture1;
	GLuint m_texture2;
	GLuint m_VAO;
};

#endif // WIDGET_H
