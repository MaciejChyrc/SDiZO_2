#pragma once
#include "GraphList.h"
#include "GraphMatrix.h"

class Dijkstra
{
public:
	Dijkstra ();
	~Dijkstra ();
	void dijkstraMatrix (int startV, GraphMatrix *graphMatrix);
	void dijkstraList (int startV, GraphList *graphList);
};