#include "show_degree.h"
#include "glwidget.h"
#include <map>

void Show_degree::onPluginLoad()
{
  map<int,int> count;
  for(unsigned int i=0; i < scene()->objects()[0].faces().size(); i++) 
    for(unsigned int j = 0; j < scene()->objects()[0].faces()[i].numVertices(); j++) {
      int v = scene()->objects()[0].faces()[i].vertexIndex(j);
      if(count.find(v) == count.end()) count[v] = 1;
      else count[v]++;
    }
  float cumulative = 0;
  for(auto& it: count) cumulative += it.second;
  degree = cumulative / count.size();

}

void Show_degree::preFrame()
{
	
}

void Show_degree::postFrame()
{
  QFont font;
  font.setPixelSize(32);
  painter.begin(glwidget());
  painter.setFont(font);
  int x = 15;
  int y = 40;
  QString n;
  painter.drawText(x, y, n.setNum(degree));    
  painter.end();
}

void Show_degree::onObjectAdd()
{
	
}

bool Show_degree::drawScene()
{
	return false; // return true only if implemented
}

bool Show_degree::drawObject(int)
{
	return false; // return true only if implemented
}

bool Show_degree::paintGL()
{
	return false; // return true only if implemented
}

void Show_degree::keyPressEvent(QKeyEvent *)
{
	
}

void Show_degree::mouseMoveEvent(QMouseEvent *)
{
	
}

