#pragma once
#include <vector>
#include "MinorStructs.h"

using namespace std;

class GraphMatrix
{
private:
	int verticesNumber, edgesNumber;
public:
	int **matrix;
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