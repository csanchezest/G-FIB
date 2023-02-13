#include "drawSmooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

DrawVBOng::~DrawVBOng() {
  cleanUp();
}

void DrawVBOng::onSceneClear()
{
    cleanUp();
}

void DrawVBOng::cleanUp()
{
  GLWidget &g = *glwidget();
  g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
  g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
  g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
  g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
  g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
  coordBuffers.clear();
  normalBuffers.clear();
  stBuffers.clear();
  colorBuffers.clear();
  VAOs.clear();
  numIndices.clear();
}

bool DrawVBOng::drawObject(int i)
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  g.glBindVertexArray(VAOs[i]);
  //g.glDrawArrays(GL_TRIANGLES, 0, numIndices[i]);
  g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*)0);
  g.glBindVertexArray(0);
  return true;
}

bool DrawVBOng::drawScene()
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  GLint program;
  g.glGetIntegerv(GL_CURRENT_PROGRAM, &program);
  GLint loc = g.glGetUniformLocation(program,"objectID");
  for(unsigned int i=0; i<VAOs.size(); i++) {
    // for each buffer (that is, for each object)
    if (loc>=0) g.glUniform1i(loc, i);
	  drawObject(i);
  }
  return true;
}

void DrawVBOng::onPluginLoad()
{
  for(unsigned int i=0; i<scene()->objects().size(); i++)
    addVBO(i);
}

void DrawVBOng::onObjectAdd()
{
  addVBO( scene()->objects().size() - 1 );
}

void DrawVBOng::addVBO(unsigned int currentObject)
{
  //
  // For simplicity, we construct VBOs with replicated vertices (a copy
  // for each triangle to which they belong:
  //
  const Object& obj = scene()->objects()[currentObject];
  //unsigned int numvertices = obj.faces().size();  // it's all triangles...
  unsigned int numvertices = obj.vertices().size()*3;  // it's all triangles...
  vector<float> vertices; // (x,y,z)    Final size: number of triangles
  vector<float> normals;  // (nx,ny,nz) Final size: number of triangles
  vector<float> colors;   // (r, g, b)  Final size: number of triangles
  vector<float> texCoords;// (s, t)     Final size: 2/3 number of triangles
  vector<unsigned int> indices;
  auto verts = obj.vertices();
  auto Ns = obj.vertNormals();
  auto texcords = obj.vertTexCoords();

  for (auto&& v: verts) {
    Point P = v.coord();
    vertices.push_back(P.x());
    vertices.push_back(P.y());
    vertices.push_back(P.z());
  }
  for (auto&& n: Ns) {
    normals.push_back(n.x());
    normals.push_back(n.y());
    normals.push_back(n.z());
    colors.push_back(fabs(n.x())); 
    colors.push_back(fabs(n.y())); 
    colors.push_back(fabs(n.z()));
  }
  for (auto&& vt: texcords) {
    texCoords.push_back(vt.first);
    texCoords.push_back(vt.second);
  }
  for (auto&& f: obj.faces()) for (int i = 0; i < f.numVertices(); i++) indices.push_back(f.vertexIndex(i));

  assert(vertices.size() == numvertices);
  assert(normals.size() == numvertices);
  assert(colors.size() == numvertices);
//   assert(texCoords.size()*3/2 == numvertices);

  // Step 2: Create VAO and empty buffers (coords, normals, ...)
  GLWidget& g = *glwidget();
  GLuint VAO;
  g.glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  g.glBindVertexArray(VAO);
  
  GLuint coordBufferID;
  g.glGenBuffers(1, &coordBufferID);
  coordBuffers.push_back(coordBufferID);
  
  GLuint normalBufferID;
  g.glGenBuffers(1, &normalBufferID);
  normalBuffers.push_back(normalBufferID);
  
  GLuint stBufferID;
  g.glGenBuffers(1, &stBufferID);
  stBuffers.push_back(stBufferID);
  
  GLuint colorBufferID;
  g.glGenBuffers(1, &colorBufferID);
  colorBuffers.push_back(colorBufferID);
  
  GLuint indexBufferID;
  g.glGenBuffers(1, &indexBufferID);
  numIndices.push_back(indices.size());
  // Step 3: Define VBO data (coords, normals, ...)
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

  g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(3);
  
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

  g.glBindVertexArray(0);
}

