#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h" 
#include <QElapsedTimer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Reflection: public QObject, public Plugin
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
    float minx, miny, minz, maxx, maxy, maxz; 
    float vminy;
    int numIndices;
    QOpenGLShaderProgram* program;
    QOpenGLShaderProgram* reflect;
    QOpenGLShaderProgram* object;
    QOpenGLShader *fs, *vs; 
    GLuint VAO;
    GLuint textureId;
};

#endif
