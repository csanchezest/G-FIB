#include "animateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad()
{
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(glwidget()->getPluginPath()+"/../animateVertices/animate-vertices1.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(glwidget()->getPluginPath()+"/../animateVertices/animate-vertices1.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    t.start();
}

void AnimateVertices::preFrame()
{
    
    program->bind();
    program->setUniformValue("amplitude", 0.1f);
    program->setUniformValue("freq", 1);
    float time = t.elapsed() / 1000.f;
    program->setUniformValue("time", time);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", normal); 
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void AnimateVertices::postFrame()
{
    program->release();
}

void AnimateVertices::onObjectAdd()
{
	
}

bool AnimateVertices::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{
	
}

