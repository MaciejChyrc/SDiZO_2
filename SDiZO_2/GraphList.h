#pragma once
#include <vector>
#include "MinorStructs.h"

using namespace std;

class GraphList
{
private:
	int verticesNumber, edgesNumber, startVertex;
	ListElement* ptr;
public:
	ListElement** adjList;
	vector<Edge> listOfEdges;
	GraphList ();
	~GraphList ();
	int getVerticesNumber ();
	int getEdgesNumber ();
	int getStartVertex ();
	void setStartVertex (int startV);
	ListElement** getAdjList (); //na wypadek zmianu adjList na private
	void createGraphFromListOfEdges (int v);
	void createDirectedGraphFromListOfEdges (int v);
	void createRandomGraph (int v, int fillPercent);
	void copyListOfEdges (vector<Edge> par);
	bool findEdge (Edge e);
	void print ();
};