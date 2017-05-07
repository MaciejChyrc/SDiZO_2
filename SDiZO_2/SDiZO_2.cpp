#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include "VertexAndEdge.h"
#include "GraphList.h"
#include "GraphMatrix.h"

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
	for (int i = 0; i < edges.size(); i++)
	{
		cout << edges[i].weight << edges[i].fromVertexId << edges[i].destVertexId << "\n";
	}
	GraphList graph;
	graph.copyListOfEdges(edges);
	graph.createGraph(3);
	graph.print();
	GraphMatrix graphM;
	//graphM.copyListOfEdges(edges);
	//graphM.createGraph(3);
	graphM.createRandomGraph(5, 80);
	for (int i = 0; i < graphM.listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphM.listOfEdges[i].weight << " " << graphM.listOfEdges[i].fromVertexId << " " << graphM.listOfEdges[i].destVertexId << "\n";
	}
	graphM.print();
	system("PAUSE");
}