#pragma once
#include <vector>
#include "MinorStructs.h"

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
	int getEdgesNumber ();
	ListElement** getAdjList (); //na wypadek zmianu adjList na private
	void createGraph (int v);
	void createRandomGraph (int v, int fillPercent);
	void copyListOfEdges (vector<Edge> par);
	void print ();
};