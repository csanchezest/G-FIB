#include "teclatSeleccio.h"
#include "glwidget.h"

void TeclatSeleccio::onPluginLoad()
{
  GLWidget & g = *glwidget();
  vector<float> vertices{0,0,0, 1,0,0, 0,0,1, 1,0,1, 0,1,0, 1,1,0, 0,1,1, 1,1,1};   // (x,y,z)
  vector<float> normals; // (nx,ny,nz)
  vector<float> colors; // (r,g,b)
  vector<float> texCoords; // (s,t)
  vector<unsigned int> indices{0,1, 0,2, 0,4, 1,5, 1,3, 2,3, 2,6, 3,7, 4,5, 4,6, 6,7, 7,5 }; //i0,i1,i2, i3,i4,i5...
  numIndices=indices.size();

  g.glGenVertexArrays(1,&VAO);
  GLuint coordBufferID;
  g.glGenBuffers(1, &coordBufferID);
  GLuint normalBufferID;
  g.glGenBuffers(1, &normalBufferID);
  GLuint colorBufferID;
  g.glGenBuffers(1, &colorBufferID);
  GLuint textBufferID;
  g.glGenBuffers(1, &textBufferID);
  GLuint indexBufferID;
  g.glGenBuffers(1, &indexBufferID);

  g.glBindVertexArray(VAO);
  g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(0);
  g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(1);
  g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(2);
  g.glBindBuffer(GL_ARRAY_BUFFER, textBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(3);
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
  g.glBindVertexArray(0);

  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../drawBoundingBox/simple.vert");
  cout << "VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../drawBoundingBox/simple.frag");
  cout << "FS log:" << fs->log().toStdString() << endl;

  program = new QOpenGLShaderProgram(this);
  program->addShader(vs);
  program->addShader(fs);
  program->link();
  cout << "Link log:" << program->log().toStdString() << endl;

  g.glDeleteBuffers(1, &coordBufferID);
  g.glDeleteBuffers(1, &normalBufferID);
  g.glDeleteBuffers(1, &colorBufferID);
  g.glDeleteBuffers(1, &textBufferID);
  g.glDeleteBuffers(1, &indexBufferID);
}

void TeclatSeleccio::preFrame()
{
	
}

void TeclatSeleccio::postFrame()
{
  program->bind();
  GLWidget & g = *glwidget();
  int seleccionat = scene()->selectedObject();
  for(unsigned int i=0; i<scene()->objects().size(); i++) {
    if(seleccionat == i) {
	Point p = scene()->objects()[i].boundingBox().min();
	Point max = scene()->objects()[i].boundingBox().max();
	minx = p.x();
	miny = p.y();
	minz = p.z();
	maxx = max.x();
	maxy = max.y();
	maxz = max.z();
	QMatrix4x4 trans = QMatrix4x4(maxx-minx, 0        , 0        , minx,
				  0        , maxy-miny, 0        , miny,
				  0        , 0        , maxz-minz, minz,
				  0        , 0        , 0        , 1.);
	program->setUniformValue("translation", trans);
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", normal); 
	program->setUniformValue("modelViewProjectionMatrix", MVP); 
	g.glBindVertexArray(VAO);
	g.glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
	g.glBindVertexArray(0);
    } else {
	QMatrix4x4 trans = QMatrix4x4(1., 0    , 0        , 0.,
				  0        , 1., 0        , 0.,
				  0        , 0        , 1., 0.,
				  0        , 0        , 0        , 1.);
	program->setUniformValue("translation", trans);
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", normal); 
	program->setUniformValue("modelViewProjectionMatrix", MVP); 
	g.glBindVertexArray(0);
    }
  }
  program->release();
}

void TeclatSeleccio::onObjectAdd()
{
	
}

bool TeclatSeleccio::drawScene()
{
	return false; // return true only if implemented
}

bool TeclatSeleccio::drawObject(int)
{
	return false; // return true only if implemented
}

bool TeclatSeleccio::paintGL()
{
	return false; // return true only if implemented
}

void TeclatSeleccio::keyPressEvent(QKeyEvent * e)
{
  GLWidget & g = *glwidget();
  g.makeCurrent();
  unsigned int selected = 0;
  if(e->key() == Qt::Key_0) {
    selected = 0;
  } else if(e->key() == Qt::Key_1) {
    selected = 1;
  } else if(e->key() == Qt::Key_2) {
    selected = 2;
  } else if(e->key() == Qt::Key_3) {
    selected = 3;
  } else if(e->key() == Qt::Key_4) {
    selected = 4;
  } else if(e->key() == Qt::Key_5) {
    selected = 5;
  } else if(e->key() == Qt::Key_6) {
    selected = 6;
  } else if(e->key() == Qt::Key_7) {
    selected = 7;
  } else if(e->key() == Qt::Key_8) {
    selected = 8;
  } else if(e->key() == Qt::Key_9) {
    selected = 9;
  }
  scene()->setSelectedObject(selected);
  g.update();
}

void TeclatSeleccio::mouseMoveEvent(QMouseEvent *)
{
	
}

