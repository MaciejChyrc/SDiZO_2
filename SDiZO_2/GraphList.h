#pragma once
#include <list>
#include <vector>
#include "VertexAndEdge.h"

using namespace std;

class GraphList
{
private:
	int verticesNumber, edgesNumber;
	ListElement* ptr;
	//vector<ListElement*> *adjList;
public:
	ListElement** adjList;
	vector<Edge> listOfEdges;
	GraphList();
	~GraphList();
	int getVerticesNumber ();
	ListElement** getAdjList ();
	void createGraph (int v);
	void copyListOfEdges (vector<Edge> par);
	void print ();
};