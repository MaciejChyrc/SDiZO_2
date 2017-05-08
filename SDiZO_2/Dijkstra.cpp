#include "Dijkstra.h"
#include <iostream>


Dijkstra::Dijkstra()
{
	graphL = nullptr;
	graphM = nullptr;
}

Dijkstra::Dijkstra(GraphList *gl, GraphMatrix *gm)
{
	graphL = gl;
	graphM = gm;
}

Dijkstra::~Dijkstra()
{
	delete graphL, graphM;
}
//do przerobienia na macierzowa reprezentacje
void Dijkstra::dijkstraMatrix(int startV, GraphMatrix *graphMatrix)
{
	graphM = graphMatrix;
	int** graph = graphMatrix->matrix;
	//ListElement* graphPtr = new ListElement;
	int verticesNumber = graphM->getVerticesNumber();
	bool* qs = new bool[verticesNumber];
	int* travelCosts = new int[verticesNumber];
	int* predecessors = new int[verticesNumber];
	int* stack = new int[verticesNumber];
	int i, j, k, stackPos = 0;

	for (i = 0; i < verticesNumber; i++)
	{
		travelCosts[i] = INT_MAX;
		predecessors[i] = -1;
		qs[i] = false;
	}

	travelCosts[startV] = 0;

	for (i = 0; i < verticesNumber; i++)
	{
		for (j = 0; qs[j]; j++);
		for (k = j++; j < verticesNumber; j++)
		{
			if (!qs[j] && (travelCosts[j] < travelCosts[k])) k = j;
		}

		qs[k] = true;
		
		//!!!PRZEROBIC TUTAJ koszty sciezek sie nie zgadzaja --- dziala, posraly mi sie iteratory 'i' i 'k'
		for (int l = 0; l < verticesNumber; l++)
		{
			while (graph[k][l] == INT_MAX) l++;
			if (!qs[l] && (travelCosts[l] > travelCosts[k] + graph[k][l]))
			{
				travelCosts[l] = travelCosts[k] + graph[k][l];
				predecessors[l] = k;
			}
		}
	}

	cout << "Algorytm Dijkstry macierzowo:\n";

	for (i = 0; i < verticesNumber; i++)
	{
		cout << i << ": ";
		for (j = i; j > -1; j = predecessors[j])
			stack[stackPos++] = j;
		while (stackPos != 0)
			cout << stack[--stackPos] << " ";
		cout << "Koszt dojscia: " << travelCosts[i] << "\n";
	}

	delete[] travelCosts, predecessors, qs, stack;
	delete graphM;
}

void Dijkstra::dijkstraList(int startV, GraphList *graphList)
{
	graphL = graphList;
	ListElement** graph = graphL->adjList;
	ListElement* graphPtr = new ListElement;
	int verticesNumber = graphL->getVerticesNumber();
	bool* qs = new bool[verticesNumber];
	int* travelCosts = new int[verticesNumber];
	int* predecessors = new int[verticesNumber];
	int* stack = new int[verticesNumber];
	int i, j, k, stackPos = 0;

	for (i = 0; i < verticesNumber; i++)
	{
		travelCosts[i] = INT_MAX;
		predecessors[i] = -1;
		qs[i] = false;
	}

	travelCosts[startV] = 0;
	
	for (i = 0; i < verticesNumber; i++)
	{
		for (j = 0; qs[j]; j++);
		for (k = j++; j < verticesNumber; j++)
		{
			if (!qs[j] && (travelCosts[j] < travelCosts[k])) k = j;
		}
		
		qs[k] = true;
		
		for (graphPtr = graph[k]; graphPtr; graphPtr = graphPtr->next)
		{
			if (!qs[graphPtr->destVertexId] && (travelCosts[graphPtr->destVertexId] > travelCosts[k] + graphPtr->weight))
			{
				travelCosts[graphPtr->destVertexId] = travelCosts[k] + graphPtr->weight;
				predecessors[graphPtr->destVertexId] = k;
			}
		}
	}

	cout << "Algorytm Dijkstry listowo:\n";

	for (i = 0; i < verticesNumber; i++)
	{
		cout << i << ": ";
		for (j = i; j > -1; j = predecessors[j])
			stack[stackPos++] = j;
		while (stackPos != 0)
			cout << stack[--stackPos] << " ";
		cout << "Koszt dojscia: " << travelCosts[i] << "\n";
	}

	delete[] travelCosts, predecessors, qs, stack;
	delete graphPtr, graphL;
}