#include "modelInfo2.h"
#include "glwidget.h"
#include <string>

void ModelInfo2::checkModelInfo() {
	strings.push_back("Num objectes: " + QString::number(scene()->objects().size()));
	for(unsigned int i=0; i<scene()->objects().size(); i++) {
		int numT = 0, total = 0;
		strings.push_back("Object " + QString::number(i) + "\n\tNum vertices: " + QString::number(scene()->objects()[i].vertices().size()));
		strings.push_back("\tNum poligons: " + QString::number(scene()->objects()[i].faces().size()));
		for(unsigned int j=0; j<scene()->objects()[i].faces().size(); j++) {
			if(scene()->objects()[i].faces()[j].numVertices()==3) numT++;
			total++;
		}
		strings.push_back("\tNum triangles(%): " + QString::number((numT/total*100)));
	}
}


void ModelInfo2::printInfo() {
  strings.clear();
  ModelInfo2::checkModelInfo();
  QFont font;
  font.setPixelSize(15);
  painter.begin(glwidget());
  painter.setFont(font);
  int x = 15;
  int y = 40;
  for(unsigned int i = 0; i < strings.size(); i++) {
    painter.drawText(x, y + 15*i, strings[i]);
  }
  painter.end();
}

void ModelInfo2::onPluginLoad()
{
	ModelInfo2::printInfo();
}

void ModelInfo2::preFrame()
{

}

void ModelInfo2::postFrame()
{
  ModelInfo2::printInfo();
}

void ModelInfo2::onObjectAdd()
{
  ModelInfo2::printInfo();
}

//bool ModelInfo::drawScene(){return false; // return true only if implemented }

//bool ModelInfo::drawObject(int){return false; // return true only if implemented }

//bool ModelInfo::paintGL(){return false; // return true only if implemented }

//void ModelInfo::keyPressEvent(QKeyEvent *){}

//void ModelInfo::mouseMoveEvent(QMouseEvent *){}


