#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad()
{
  GLWidget & g = *glwidget();
  vector<float> vertices{0,0,0, 1,0,0, 0,0,1, 1,0,1, 0,1,0, 1,1,0, 0,1,1, 1,1,1};   // (x,y,z)
  vector<float> normals; // (nx,ny,nz)
  vector<float> colors; // (r,g,b)
  vector<float> texCoords; // (s,t)
  vector<unsigned int> indices{0,4,1, 1,4,5, 1,5,3, 3,5,7, 3,7,6, 2,3,6, 0,2,6, 0,6,4, 4,6,7, 5,4,7, 0,1,3, 0,3,2}; //i0,i1,i2, i3,i4,i5...
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

void DrawBoundingBox::preFrame()
{

}

void DrawBoundingBox::postFrame()
{
  program->bind();
  GLWidget & g = *glwidget();
  for(unsigned int i=0; i<scene()->objects().size(); i++) {
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
    g.glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
    g.glBindVertexArray(0);
  }
  program->release();
}

void DrawBoundingBox::onObjectAdd()
{
	
}

bool DrawBoundingBox::drawScene()
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::drawObject(int)
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::paintGL()
{
	return false; // return true only if implemented
}

void DrawBoundingBox::keyPressEvent(QKeyEvent *)
{
	
}

void DrawBoundingBox::mouseMoveEvent(QMouseEvent *)
{
	
}

