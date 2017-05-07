#pragma once
#include <list>
#include <vector>
#include "VertexAndEdge.h"

using namespace std;

class GraphMatrix
{
private:
	int verticesNumber, edgesNumber;
	int **matrix;
public:
	vector<Edge> listOfEdges;
	GraphMatrix();
	~GraphMatrix();
	int getVerticesNumber ();
	int** getMatrix ();
	void createGraph (int v);
	void createRandomGraph (int v, int fillPercent);
	void copyListOfEdges (vector<Edge> par);
	void print ();
};