#ifndef _DISTORT_H
#define _DISTORT_H

#include "plugin.h" 
#include <QElapsedTimer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Distort: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId;
    QElapsedTimer t;
};

#endif
