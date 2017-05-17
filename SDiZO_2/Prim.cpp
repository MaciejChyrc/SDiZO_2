#include "Prim.h"
#include  <vector>
#include "MyQueue.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "MinSpanningTree.h"
#include <iostream>
#include "windows.h"

using namespace std;

Prim::Prim()
{
	
}

Prim::~Prim()
{
	
}
///<note>Algorytm Prima dla reprezentacji macierzowej. Przyjmuje dodatkowy parametr
///<note>w postaci vectora, do ktorego zapisuje czas wykonania algorytmu.
///<note>Metoda statyczna - nie wymaga utworzenia obiektu Prim.
void Prim::primMatrix(int startV, GraphMatrix *graphMatrix, vector<double> &vectorOfTimes)
{
	long long int frequency, timeStart, timeElapsed;
	int** graph = graphMatrix->matrix;
	int verticesNumber = graphMatrix->getVerticesNumber();
	bool* visited = new bool[verticesNumber];
	vector<Edge> edges = graphMatrix->listOfEdges;
	MinSpanningTree mst(verticesNumber);
	MyQueue q;
	Edge edge;
	int i, x;

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();

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
	
	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000.0);

	mst.createTreeFromListOfEdges(verticesNumber);
	cout << "Minimalne drzewo rozpinajace algorytmem Prima\nwykonane na grafie jako macierzy:\n";
	mst.printListOfEdges();

	delete[] visited;
}
///<note>Algorytm Prima dla reprezentacji listowej. Przyjmuje dodatkowy parametr
///<note>w postaci vectora, do ktorego zapisuje czas wykonania algorytmu.
///<note>Metoda statyczna - nie wymaga utworzenia obiektu Prim.
void Prim::primList(int startV, GraphList * graphList, vector<double> &vectorOfTimes)
{
	long long int frequency, timeStart, timeElapsed;
	ListElement** graph = graphList->adjList;
	ListElement* graphPtr = new ListElement;
	int verticesNumber = graphList->getVerticesNumber();
	bool* visited = new bool[verticesNumber];
	vector<Edge> edges = graphList->listOfEdges;
	MinSpanningTree mst;
	MyQueue q;
	Edge edge;
	int i, x;

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();

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

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000.0);

	mst.createTreeFromListOfEdges(verticesNumber);
	cout << "Minimalne drzewo rozpinajace algorytmem Prima\nwykonane na grafie jako tablicy list:\n";
	mst.printListOfEdges();

	delete[] visited;
	delete graphPtr;
}
//-----------------------------------------------------------------------------
long long int Prim::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return static_cast<long long int>(count.QuadPart);
}