#include "modelInfo.h"
#include "glwidget.h"

void ModelInfo::checkModelInfo() {
	cout<<"Num objectes: "<<scene()->objects().size()<<endl;
	for(int i=0; i<scene()->objects().size(); i++) {
		int numT = 0, total = 0;
		cout<<"Object "<<i<<"\n\tNum vertices: "<<scene()->objects()[i].vertices().size()<<endl;
		cout<<"\tNum poligons: "<<scene()->objects()[i].faces().size()<<endl;
		for(int j=0; j<scene()->objects()[i].faces().size(); j++) {
			if(scene()->objects()[i].faces()[j].numVertices()==3) numT++;
			total++;
		}
		cout<<"\tNum triangles(%): "<<numT/total*100<<endl;
	}
}

void ModelInfo::onPluginLoad(){ModelInfo::checkModelInfo();}

//void ModelInfo::preFrame(){}



void ModelInfo::postFrame() {

}

void ModelInfo::onObjectAdd(){ModelInfo::checkModelInfo();}

//bool ModelInfo::drawScene(){return false; // return true only if implemented }

//bool ModelInfo::drawObject(int){return false; // return true only if implemented }

//bool ModelInfo::paintGL(){return false; // return true only if implemented }

//void ModelInfo::keyPressEvent(QKeyEvent *){}

//void ModelInfo::mouseMoveEvent(QMouseEvent *){}

