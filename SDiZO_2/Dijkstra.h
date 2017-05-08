#pragma once
#include "GraphList.h"
#include "GraphMatrix.h"

class Dijkstra
{
private:
	GraphList* graphL;
	GraphMatrix* graphM;
public:
	Dijkstra ();
	Dijkstra(GraphList *gl, GraphMatrix *gm);
	~Dijkstra();
	void dijkstraMatrix (int startV, GraphMatrix *graphMatrix);
	void dijkstraList (int startV, GraphList *graphList);
};