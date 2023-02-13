#include "reflection.h"
#include "glwidget.h"

const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::onPluginLoad()
{
  GLWidget & g = *glwidget();
  vector<float> vertices{0,0,0, 1,0,0, 0,0,1, 1,0,1};   // (x,y,z)
  vector<float> normals; // (nx,ny,nz)
  vector<float> colors; // (r,g,b)
  vector<float> texCoords; // (s,t)
  vector<unsigned int> indices{0,2,3, 0,3,1}; //i0,i1,i2, i3,i4,i5...
  //vector<unsigned int> indices{0,2,1, 2,3,1}; //i0,i1,i2, i3,i4,i5...
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
  // texturing
  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/simple.vert");
  cout << "VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/simple.frag");
  cout << "FS log:" << fs->log().toStdString() << endl;

  program = new QOpenGLShaderProgram(this);
  program->addShader(vs);
  program->addShader(fs);
  program->link();
  cout << "Link log:" << program->log().toStdString() << endl;
  //reflection
  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/invert.vert");
  cout << "VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/invert.frag");
  cout << "FS log:" << fs->log().toStdString() << endl;

  reflect = new QOpenGLShaderProgram(this);
  reflect->addShader(vs);
  reflect->addShader(fs);
  reflect->link();
  cout << "Link log:" << reflect->log().toStdString() << endl;
  //normal
  vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
  vs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/normal.vert");
  cout << "VS log:" << vs->log().toStdString() << endl;

  fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
  fs->compileSourceFile(glwidget()->getPluginPath()+"/../reflection/normal.frag");
  cout << "FS log:" << fs->log().toStdString() << endl;

  object = new QOpenGLShaderProgram(this);
  object->addShader(vs);
  object->addShader(fs);
  object->link();
  cout << "Link log:" << object->log().toStdString() << endl;

  // Setup texture
  g.glActiveTexture(GL_TEXTURE0);
  g.glGenTextures( 1, &textureId);
  g.glBindTexture(GL_TEXTURE_2D, textureId);
  g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
  g.glBindTexture(GL_TEXTURE_2D, 0);
  // Resize to power-of-two viewport
  g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);

  g.glDeleteBuffers(1, &coordBufferID);
  g.glDeleteBuffers(1, &normalBufferID);
  g.glDeleteBuffers(1, &colorBufferID);
  g.glDeleteBuffers(1, &textBufferID);
  g.glDeleteBuffers(1, &indexBufferID);
}

void Reflection::preFrame()
{

}

void Reflection::postFrame()
{
  /*program->bind();
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
  program->release();*/
}

void Reflection::onObjectAdd()
{
  /*const Object& obj = scene()->objects()[0];
  auto verts = obj.vertices();
  vminy = verts[0].coord().y();
  float y;
  for (auto&& v: verts) {
    y = v.coord().y();
    if(y>vminy) vminy = y;
  }*/
}

bool Reflection::drawScene()
{
	return false; // return true only if implemented
}

bool Reflection::drawObject(int)
{
	return false; // return true only if implemented
}

bool Reflection::paintGL()
{
  GLWidget & g = *glwidget();
  // Pasa 1. Dibuixar escena reflectida en el pla del mirall
  g.glClearColor(0,0,0,0);
  g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  reflect->bind();
  QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
  QMatrix3x3 normal = camera()->viewMatrix().normalMatrix();
  reflect->setUniformValue("normalMatrix", normal); 
  reflect->setUniformValue("modelViewProjectionMatrix", MVP); 
  reflect->setUniformValue("vmin", scene()->objects()[0].boundingBox().min().y()); 
  if (drawPlugin()) drawPlugin()->drawScene();
  // Get texture
  g.glBindTexture(GL_TEXTURE_2D, textureId);
  g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

  // Pasa 2. Esborrar framebuffer i dibuixar escena en posicio real
  g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 

  object->bind();
  MVP = camera()->projectionMatrix() * camera()->viewMatrix();
  normal = camera()->viewMatrix().normalMatrix();
  object->setUniformValue("normalMatrix", normal); 
  object->setUniformValue("modelViewProjectionMatrix", MVP); 
  if (drawPlugin()) drawPlugin()->drawScene();
  
  // Pasa 3. Dibuixa el mirall texturat
  program->bind();
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
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("translation", trans);
    program->setUniformValue("size", (float)IMAGE_WIDTH);
//std::cout << IMAGE_WIDTH << std::endl;
    MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    normal = camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", normal); 
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    g.glBindVertexArray(VAO);
    g.glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
    g.glBindVertexArray(0);
  }
  program->release();

  g.defaultProgram()->bind();
  g.glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

void Reflection::keyPressEvent(QKeyEvent *)
{
	
}

void Reflection::mouseMoveEvent(QMouseEvent *)
{
	
}

