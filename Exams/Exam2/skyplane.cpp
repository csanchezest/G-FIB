#include "skyplane.h"
#include "glwidget.h"
#include <camera.h>

void Skyplane::onPluginLoad()
{
	GLWidget & g = *glwidget();
	// Mirror shaders
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/shaders/mirror.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/shaders/mirror.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	mirror = new QOpenGLShaderProgram(this);
	mirror->addShader(vs);
	mirror->addShader(fs);
	mirror->link();
	cout << "Link log:" << mirror->log().toStdString() << endl;
	// Sky shaders
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/shaders/sky.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/shaders/sky.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	sky = new QOpenGLShaderProgram(this);
	sky->addShader(vs);
	sky->addShader(fs);
	sky->link();
	cout << "Link log:" << sky->log().toStdString() << endl;

	QString fileName = QFileDialog::getOpenFileName(&g, tr("Open File"),
		                                  "~/assig/grau-g/",
		                                  tr("Images (*.png *.xpm *.jpg)"));
	image = QImage(fileName);
	image = image.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &texture);
	g.glBindTexture(GL_TEXTURE_2D, texture);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void Skyplane::preFrame()
{
	
}

void Skyplane::postFrame()
{
	
}

void Skyplane::onObjectAdd()
{
	
}

void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);
	float z = Camera().zfar();
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, z, 
                            1, -1, z, 
                           -1,  1, z, 
                            1,  1, z};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

bool Skyplane::drawScene()
{
	return false; // return true only if implemented
}

bool Skyplane::drawObject(int)
{
	return false; // return true only if implemented
}

bool Skyplane::paintGL()
{
	// Passa 1
    	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLWidget & g = *glwidget();
	g.glActiveTexture(GL_TEXTURE0); 
	g.glBindTexture(GL_TEXTURE_2D, texture);

	sky->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
  	QMatrix4x4 MV = camera()->viewMatrix();
  	sky->setUniformValue("modelViewMatrix", MV); 
  	sky->setUniformValue("modelViewProjectionMatrix", MVP); 
	sky->setUniformValue("sampler0", 0);

    	drawRect(g);

	// Passa 2

	mirror->bind();
	MVP = camera()->projectionMatrix() * camera()->viewMatrix();
  	MV = camera()->viewMatrix();
  	mirror->setUniformValue("modelViewMatrix", MV); 
  	mirror->setUniformValue("modelViewProjectionMatrix", MVP); 
	mirror->setUniformValue("sampler0", 0);
    	if (drawPlugin()) drawPlugin()->drawScene();
    	return true;
}

void Skyplane::keyPressEvent(QKeyEvent *)
{
	
}

void Skyplane::mouseMoveEvent(QMouseEvent *)
{
	
}

