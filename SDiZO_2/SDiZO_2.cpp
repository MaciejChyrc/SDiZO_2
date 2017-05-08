#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include "MinorStructs.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Dijkstra.h";

using namespace std;

int main ()
{
	vector<Edge> edges;
	Edge edge;
	edge.weight = 3; edge.fromVertexId = 0; edge.destVertexId = 1;
	edges.push_back(edge);
	edge.weight = 1; edge.fromVertexId = 1; edge.destVertexId = 2;
	edges.push_back(edge);
	edge.weight = 2; edge.fromVertexId = 2; edge.destVertexId = 0;
	edges.push_back(edge);
	edge.weight = 6; edge.fromVertexId = 3; edge.destVertexId = 1;
	edges.push_back(edge);
	edge.weight = 5; edge.fromVertexId = 2; edge.destVertexId = 3;
	edges.push_back(edge);
	edge.weight = 8; edge.fromVertexId = 0; edge.destVertexId = 4;
	edges.push_back(edge);
	for (int i = 0; i < edges.size(); i++)
	{
		cout << edges[i].weight << edges[i].fromVertexId << edges[i].destVertexId << "\n";
	}
	GraphList *graphL = new GraphList();
	graphL->copyListOfEdges(edges);
	graphL->createGraph(5);
	graphL->print();
	GraphMatrix *graphM = new GraphMatrix();
	//graphM.copyListOfEdges(edges);
	//graphM.createGraph(3);
	graphM->createRandomGraph(10, 25);
	for (int i = 0; i < graphM->listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphM->listOfEdges[i].weight << " " << graphM->listOfEdges[i].fromVertexId << " " << graphM->listOfEdges[i].destVertexId << "\n";
	}
	graphM->print();
	Dijkstra* dijkstra = new Dijkstra ();
	dijkstra->dijkstraList(1, graphL);
	dijkstra->dijkstraMatrix(1, graphM);
	system("PAUSE");
}