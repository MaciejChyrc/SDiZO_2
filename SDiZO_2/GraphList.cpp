#include "GraphList.h"
#include <iostream>


GraphList::GraphList()
{
	verticesNumber = 0;
	edgesNumber = 0;
	adjList = nullptr;
	ptr = nullptr;
}

GraphList::~GraphList()
{

}

int GraphList::getVerticesNumber()
{
	return verticesNumber;
}

ListElement ** GraphList::getAdjList()
{
	return adjList;
}

void GraphList::createGraph(int v)
{
	adjList = new ListElement*[v];
	edgesNumber = listOfEdges.size();
	verticesNumber = v;
	vector<Edge> tempListOfEdges = listOfEdges;
	int v1, v2, w;

	for (int i = 0; i < v; i++)
	{
		adjList[i] = nullptr;
	}
	for (int i = 0; i < tempListOfEdges.size(); i++)
	{
		v1 = tempListOfEdges[i].fromVertexId;
		v2 = tempListOfEdges[i].destVertexId;
		w = tempListOfEdges[i].weight;
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v2;
		ptr->next = adjList[v1];
		adjList[v1] = ptr;
		//krawedz odwrotna do dodanej (tworzymy w ten sposob "niby skierowany" graf)
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v1;
		ptr->next = adjList[v2];
		adjList[v2] = ptr;
	}
	/*adjList = new vector<ListElement*>[v];
	ListElement* temp;
	list<Edge> tempListOfEdges = listOfEdges;
	while (!tempListOfEdges.empty())
	{
		temp = new ListElement;
		temp->weight = tempListOfEdges.front().weight;
		temp->destVertexId = tempListOfEdges.front().destVertexId;
		adjList[tempListOfEdges.front().fromVertexId].push_back(temp);
		temp->destVertexId = tempListOfEdges.front().fromVertexId;
		adjList[tempListOfEdges.front().destVertexId].push_back(temp);
	}*/
}
//dodajemy do klasy liste krawedzi wczytana poza klasa (np. z pliku)
void GraphList::copyListOfEdges(vector<Edge> par)
{
	listOfEdges = par;
}

void GraphList::print()
{
	cout << "Reprezentacja listowa:\n";
	for (int i = 0; i < verticesNumber; i++)
	{
		cout << i << ": ";
		ptr = adjList[i];
		while (ptr != nullptr)
		{
			cout << ptr->weight << ptr->destVertexId << " ";
			ptr = ptr->next;
		}
		cout << "\n";
	}
}