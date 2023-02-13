#include "textureSplatting.h"
#include "glwidget.h"

void TextureSplatting::onPluginLoad()
{
	GLWidget & g = *glwidget();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile(glwidget()->getPluginPath()+"/../textureSplatting/splatting.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile(glwidget()->getPluginPath()+"/../textureSplatting/splatting.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;

	QString fileName = QFileDialog::getOpenFileName(&g, tr("Open File"),
		                                  "/home/dades/cristian.sanchez.estape/G/NewViewer_c2dcae3/",
		                                  tr("Images (*.png *.xpm *.jpg)"));
	noiseI = QImage(fileName);
	noiseI = noiseI.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &noise);
	g.glBindTexture(GL_TEXTURE_2D, noise);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, noiseI.width(), noiseI.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, noiseI.bits());
	g.glBindTexture(GL_TEXTURE_2D, 0);

	fileName = QFileDialog::getOpenFileName(&g, tr("Open File"),
		                                  "/home/dades/cristian.sanchez.estape/G/NewViewer_c2dcae3/",
		                                  tr("Images (*.png *.xpm *.jpg)"));
	rockI = QImage(fileName);
	rockI = rockI.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &rock);
	g.glBindTexture(GL_TEXTURE_2D, rock);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rockI.width(), rockI.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, rockI.bits());
	g.glBindTexture(GL_TEXTURE_2D, 0);

	fileName = QFileDialog::getOpenFileName(&g, tr("Open File"),
		                                  "/home/dades/cristian.sanchez.estape/G/NewViewer_c2dcae3/",
		                                  tr("Images (*.png *.xpm *.jpg)"));
	grassI = QImage(fileName);
	grassI = grassI.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &grass);
	g.glBindTexture(GL_TEXTURE_2D, grass);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, grassI.width(), grassI.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, grassI.bits());
	g.glBindTexture(GL_TEXTURE_2D, 0);

}

void TextureSplatting::preFrame()
{
	program->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", normal); 
	program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void TextureSplatting::postFrame()
{
	program->release();
}

void TextureSplatting::onObjectAdd()
{
	
}

bool TextureSplatting::drawScene()
{
	return false; // return true only if implemented
}

bool TextureSplatting::drawObject(int)
{
	return false; // return true only if implemented
}

bool TextureSplatting::paintGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLWidget & g = *glwidget();
	g.glActiveTexture(GL_TEXTURE0); 
	g.glBindTexture(GL_TEXTURE_2D, noise);

	g.glActiveTexture(GL_TEXTURE1); 
	g.glBindTexture(GL_TEXTURE_2D, rock);

	g.glActiveTexture(GL_TEXTURE2); 
	g.glBindTexture(GL_TEXTURE_2D, grass);

	program->bind();
	program->setUniformValue("noise0", 0);
	program->setUniformValue("rock1", 1);
	program->setUniformValue("grass2", 2);

    if (drawPlugin()) 
        drawPlugin()->drawScene();

    glwidget()->drawAxes();

    return true;
}

void TextureSplatting::keyPressEvent(QKeyEvent *)
{
	
}

void TextureSplatting::mouseMoveEvent(QMouseEvent *)
{
	
}

