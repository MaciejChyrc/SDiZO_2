#pragma once
#include <vector>
#include "MinorStructs.h"

class MinSpanningTree
{
private:
	ListElement** adjList;
	ListElement* ptr;
	int verticesNumber, edgesNumber, weight;
public:
	std::vector<Edge> listOfEdges;
	MinSpanningTree ();
	MinSpanningTree (int v);
	~MinSpanningTree ();
	void createTreeFromListOfEdges (int v);
	void add (Edge edge);
	ListElement* getAdjList (int i);
	void printAdjacencyList ();
	void printListOfEdges ();
};