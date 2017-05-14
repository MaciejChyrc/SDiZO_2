#include "Prim.h"
#include  <vector>
#include "MyQueue.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "MinSpanningTree.h"
#include <iostream>

using namespace std;

Prim::Prim()
{
	
}

Prim::~Prim()
{
	
}
//sprawdzenie iteratorow trzeba zrobic
void Prim::primMatrix(int startV, GraphMatrix * graphMatrix)
{
	int** graph = graphMatrix->matrix;
	int verticesNumber = graphMatrix->getVerticesNumber();
	bool* visited = new bool[verticesNumber];
	vector<Edge> edges = graphMatrix->listOfEdges;
	MinSpanningTree mst(verticesNumber);
	MyQueue q;
	Edge edge;
	int i, x;

	for (i = 0; i < verticesNumber; i++)
	{
		visited[i] = false;
	}

	x = startV;
	visited[x] = true;
	//1 krok mniej od ilosci wierzcholkow, bo V startowy juz jest odwiedzony
	for (i = 1; i < verticesNumber; i++)
	{
		for (int l = 0; l < verticesNumber; l++)
		{
			if (!visited[l])
			{
				edge.fromVertexId = x;
				edge.destVertexId = l;
				edge.weight = graph[x][l];
				q.push(edge);
			}
		}
		do
		{
			edge = q.front();
			q.pop();
		} while (visited[edge.destVertexId]);

		mst.add(edge);
		visited[edge.destVertexId] = true;
		x = edge.destVertexId;
	}

	mst.createTreeFromListOfEdges(verticesNumber);
	cout << "Minimalne drzewo rozpinajace algorytmem Prima\nwykonane na grafie jako macierzy:\n";
	//mst.printAdjacencyList();
	mst.printListOfEdges();

	delete[] visited;
}
//chyba dziala
void Prim::primList(int startV, GraphList * graphList)
{
	ListElement** graph = graphList->adjList;
	ListElement* graphPtr = new ListElement;
	int verticesNumber = graphList->getVerticesNumber();
	bool* visited = new bool[verticesNumber];
	vector<Edge> edges = graphList->listOfEdges;
	MinSpanningTree mst;
	MyQueue q;
	Edge edge;
	int i, x;

	for (i = 0; i < verticesNumber; i++)
	{
		visited[i] = false;
	}
	
	x = startV;
	visited[startV] = true;
	//1 krok mniej od ilosci wierzcholkow, bo V startowy juz jest odwiedzony
	for (i = 1; i < verticesNumber; i++)
	{
		for (graphPtr = graph[x]; graphPtr; graphPtr = graphPtr->next)
		{
			if (!visited[graphPtr->destVertexId])
			{
				edge.fromVertexId = x;
				edge.destVertexId = graphPtr->destVertexId;
				edge.weight = graphPtr->weight;
				q.push(edge);
			}
		}
		do
		{
			edge = q.front();
			q.pop();
		} while (visited[edge.destVertexId]);

		mst.add(edge);
		visited[edge.destVertexId] = true;
		x = edge.destVertexId;
	}

	mst.createTreeFromListOfEdges(verticesNumber);
	cout << "Minimalne drzewo rozpinajace algorytmem Prima\nwykonane na grafie jako tablicy list:\n";
	//mst.printAdjacencyList();
	mst.printListOfEdges();

	delete[] visited;
	delete graphPtr;
}