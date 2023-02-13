#include "mouseSeleccio.h"
#include "glwidget.h"
#include <QVector>

void MouseSeleccio::onPluginLoad()
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
  // COLOR
  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../mouseSeleccio/color.vert");
  cout << "color VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../mouseSeleccio/color.frag");
  cout << "color FS log:" << fs->log().toStdString() << endl;

  color = new QOpenGLShaderProgram(this);
  color->addShader(vs);
  color->addShader(fs);
  color->link();
  cout << "Link color log:" << color->log().toStdString() << endl;
  // box
  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../mouseSeleccio/box.vert");
  cout << "box VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../mouseSeleccio/box.frag");
  cout << "box FS log:" << fs->log().toStdString() << endl;

  box = new QOpenGLShaderProgram(this);
  box->addShader(vs);
  box->addShader(fs);
  box->link();
  cout << "Link box log:" << box->log().toStdString() << endl;

  g.glDeleteBuffers(1, &coordBufferID);
  g.glDeleteBuffers(1, &normalBufferID);
  g.glDeleteBuffers(1, &colorBufferID);
  g.glDeleteBuffers(1, &textBufferID);
  g.glDeleteBuffers(1, &indexBufferID);
}

void MouseSeleccio::preFrame()
{

}

void MouseSeleccio::postFrame()
{
  box->bind();
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
	box->setUniformValue("translation", trans);
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	box->setUniformValue("normalMatrix", normal); 
	box->setUniformValue("modelViewProjectionMatrix", MVP);
	g.glBindVertexArray(VAO);
	g.glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
	g.glBindVertexArray(0);
    } else {
	QMatrix4x4 trans = QMatrix4x4(1., 0    , 0        , 0.,
				  0        , 1., 0        , 0.,
				  0        , 0        , 1., 0.,
				  0        , 0        , 0        , 1.);
	box->setUniformValue("translation", trans);
	//program->setUniformValue("color", QVector4D(1,0,0,0)); 
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	box->setUniformValue("normalMatrix", normal); 
	box->setUniformValue("modelViewProjectionMatrix", MVP); 
	g.glBindVertexArray(0);
    }
  }
  box->release();
}

void MouseSeleccio::onObjectAdd()
{
	
}

bool MouseSeleccio::drawScene()
{
	return false; // return true only if implemented
}

bool MouseSeleccio::drawObject(int)
{
	return false; // return true only if implemented
}

bool MouseSeleccio::paintGL()
{
	return false; // return true only if implemented
}

void MouseSeleccio::keyPressEvent(QKeyEvent *)
{
	
}

void MouseSeleccio::mouseMoveEvent(QMouseEvent *)
{
	
}

void encodeID(int index, GLubyte* color) {
	color[0] = color[1] = color[2] = index;
}

int decodeID(int color) {
	if (color == 255) return -1;
	return color;
}

void MouseSeleccio::mouseReleaseEvent(QMouseEvent * e)
{
	// a) Comprovar que efectivament s’ha fet click amb el botó adient i els modificadors (Shift, Control...) adients
	if(e->button() != Qt::LeftButton) return;
	if(e->modifiers() != Qt::ControlModifier) return;

  	GLWidget & g = *glwidget();
	g.makeCurrent();

	// b) Esborrar els buffers amb un color de fons únic (ex. blanc)
	g.glClearColor(1,1,1,1);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// c) Activar (bind) el shader program amb el VS+FS d’abans.
	color->bind();

	// d) Enviar els uniforms que facin servir els vostres shaders
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
	color->setUniformValue("normalMatrix", normal); 
	color->setUniformValue("modelViewProjectionMatrix", MVP); 
	
	// e) Pintar l'escena assegurant-se que cada objecte es pinta amb un color únic que permeti identificar l'objecte (i diferent del color de fons)
	// per cada objecte
	for(unsigned int i=0; i<scene()->objects().size(); ++i) {
		GLubyte colorvec[4];
		encodeID(i,colorvec); //trieu la conversió que volgueu
		color->setUniformValue("color",QVector4D(colorvec[0]/255.0,colorvec[1]/255.,colorvec[2]/255.,1.0));
		drawPlugin()->drawObject(i);
	} 
	color->release();
	// f) Llegir el color del buffer de color sota la posició del cursor
	int x=e->x();
	int y=glwidget()->height()-e->y();
	GLubyte read[4];
	glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,read);
	
	// g) Obtenir l'identificador de l'objecte corresponent i, si no és color de fons, establir l'objecte seleccionat amb el mètode setSelectedObject de la classe Scene
	int selected = decodeID(read[0]);
	scene()->setSelectedObject(selected);

	// h) Cridar a update per tal que es repinti l'escena
	g.update();
}


