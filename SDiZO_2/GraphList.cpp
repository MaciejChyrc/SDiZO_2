#include "GraphList.h"
#include <iostream>
#include <ctime>


GraphList::GraphList()
{
	verticesNumber = 0;
	edgesNumber = 0;
	adjList = nullptr;
	ptr = nullptr;
}

GraphList::~GraphList()
{
	ListElement* dltPtr;	//pomocniczy wskaznik do usuwania elementow list
	for (int i = 0; i < verticesNumber; i++)
	{
		ptr = adjList[i];
		while (ptr != nullptr)
		{
			dltPtr = ptr;
			ptr = ptr->next;
			delete dltPtr;
		}
	}
	delete[] adjList;
	delete ptr;
}

int GraphList::getVerticesNumber()
{
	return verticesNumber;
}

int GraphList::getEdgesNumber()
{
	return edgesNumber;
}

ListElement** GraphList::getAdjList()
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

void GraphList::createRandomGraph(int v, int fillPercent)
{
	if (fillPercent > 99 || fillPercent < 25)
	{
		cout << "Nieakceptowany wspolczynnik gestosci grafu. Podaj wartosc od 25 do 99.\n";
		return;
	}

	srand(time(NULL));
	int edgesToCreate = static_cast<double>(fillPercent) / 100 * (static_cast<double>(v) * (static_cast<double>(v) - 1)) / 2;

	if (edgesToCreate < (v - 1))
	{
		cout << "Nieprawidlowy wspolczynnik gestosci grafu.\n";
		cout << "Nie uda sie przy takiej gestosci uzyskac grafu spojnego.\n";
		return;
	}
	adjList = new ListElement*[v];
	verticesNumber = v;
	edgesNumber = edgesToCreate;

	for (int i = 0; i < v; i++)
	{
		adjList[i] = nullptr;
	}

	int v1, v2, w;
	Edge* edge = nullptr;

	for (int i = 0; i < v - 1; i++, edgesToCreate--)
	{
		v2 = i + 1;
		w = rand() % 10 + 1;
		edge = new Edge(w, i, v2);
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v2;
		ptr->next = adjList[i];
		adjList[i] = ptr;	
		//krawedz odwrotna do dodanej (tworzymy w ten sposob "niby skierowany" graf)
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = i;
		ptr->next = adjList[v2];
		adjList[v2] = ptr;
		listOfEdges.push_back(*edge);
	}
	for (int i = 0; i < edgesToCreate; i++)
	{
		v1 = rand() % v;
		v2 = rand() % v;
		w = rand() % 10 + 1;
		edge = new Edge(w, v1, v2);
		while (v1 == v2 || findEdge(*edge))
		{
			v1 = rand() % v;
			v2 = rand() % v;
			edge = new Edge(w, v1, v2); //bez tego moglo sie zapetlic bo jak raz krawedz juz istniala
		}								//to sprawdzalo warunek petli dla starych wierzcholkow i zwracalo zawsze true
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v2;
		ptr->next = adjList[v1];
		adjList[v1] = ptr;
		
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v1;
		ptr->next = adjList[v2];
		adjList[v2] = ptr;	
		listOfEdges.push_back(*edge);
	}
	delete edge;
}
//dodajemy do klasy liste krawedzi wczytana poza klasa (np. z pliku)
void GraphList::copyListOfEdges(vector<Edge> par)
{
	listOfEdges = par;
}

bool GraphList::findEdge(Edge e)
{
	for (Edge edge : listOfEdges)
	{
		if (e.weight == edge.weight && e.destVertexId == edge.destVertexId && e.fromVertexId == edge.fromVertexId)
			return true;
		else if (e.weight == edge.weight && e.destVertexId == edge.fromVertexId && e.fromVertexId == edge.destVertexId)
			return true;
	}
	return false;
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