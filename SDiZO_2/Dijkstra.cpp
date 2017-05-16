#include "Dijkstra.h"
#include <iostream>
//#include <vector>
#include "windows.h"

using namespace std;

Dijkstra::Dijkstra()
{

}

Dijkstra::~Dijkstra()
{
	
}

void Dijkstra::dijkstraMatrix(int startV, GraphMatrix *graphMatrix, vector<double> &vectorOfTimes)
{
	long long int frequency, timeStart, timeElapsed;
	int** graph = graphMatrix->matrix;
	int verticesNumber = graphMatrix->getVerticesNumber();
	bool* qs = new bool[verticesNumber];
	int* travelCosts = new int[verticesNumber];
	int* predecessors = new int[verticesNumber];
	int* stack = new int[verticesNumber];
	int i, j, k, stackPos = 0;

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();

	for (i = 0; i < verticesNumber; i++)
	{
		travelCosts[i] = INT_MAX;
		predecessors[i] = -1;
		qs[i] = false;
	}

	travelCosts[startV] = 0;

	for (i = 0; i < verticesNumber; i++)
	{
		for (j = 0; qs[j]; j++); //szukamy elementu jeszcze nie dodanego do zbioru S
		for (k = j++; j < verticesNumber; j++)
		{
			if (!qs[j] && (travelCosts[j] < travelCosts[k])) k = j;
		}

		qs[k] = true;
		
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

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000.0);

	cout << "Algorytm Dijkstry macierzowo:\n";
	cout << "Startowy wierzcholek: " << startV << "\n";
	for (i = 0; i < verticesNumber; i++)
	{		
		cout << "End Dist Path\n";
		if (i >= 10 && travelCosts[i] >= 10)
			cout << i << " | " << travelCosts[i] << " | ";
		else if (i >= 10 && travelCosts[i] < 10)
			cout << i << " | " << travelCosts[i] << "  | ";
		else if (i < 10 && travelCosts[i] >= 10)
			cout << i << "  | " << travelCosts[i] << " | ";
		else if (i < 10 && travelCosts[i] < 10)
			cout << i << "  | " << travelCosts[i] << "  | ";
		for (j = i; j > -1; j = predecessors[j])
			stack[stackPos++] = j;
		while (stackPos != 0)
			cout << stack[--stackPos] << " ";
		cout << "\n";
	}

	delete[] travelCosts, predecessors, qs, stack;
}

void Dijkstra::dijkstraList(int startV, GraphList *graphList, vector<double> &vectorOfTimes)
{
	long long int frequency, timeStart, timeElapsed;
	ListElement** graph = graphList->adjList;
	ListElement* graphPtr = new ListElement;
	int verticesNumber = graphList->getVerticesNumber();
	bool* qs = new bool[verticesNumber];
	int* travelCosts = new int[verticesNumber];
	int* predecessors = new int[verticesNumber];
	int* stack = new int[verticesNumber];
	int i, j, k, stackPos = 0;

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();

	for (i = 0; i < verticesNumber; i++)
	{
		travelCosts[i] = INT_MAX;
		predecessors[i] = -1;
		qs[i] = false;
	}

	travelCosts[startV] = 0;
	
	for (i = 0; i < verticesNumber; i++)
	{
		for (j = 0; qs[j]; j++); //szukamy elementu jeszcze nie dodanego do zbioru S
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

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000.0);

	cout << "Algorytm Dijkstry listowo:\n";
	cout << "Startowy wierzcholek: " << startV << "\n";
	for (i = 0; i < verticesNumber; i++)
	{
		cout << "End Dist Path\n";
		if (travelCosts[i] == INT_MAX)
			cout << i << " | " << "Brak polaczenia do " << i << " wierzcholka.\n";
		else if (i >= 10 && travelCosts[i] >= 10 && travelCosts[i] < INT_MAX)
		{
			cout << i << " | " << travelCosts[i] << " | ";
			for (j = i; j > -1; j = predecessors[j])
				stack[stackPos++] = j;
			while (stackPos != 0)
				cout << stack[--stackPos] << " ";
			cout << "\n";
		}
		else if (i >= 10 && travelCosts[i] < 10)
		{
			cout << i << " | " << travelCosts[i] << "  | ";
			for (j = i; j > -1; j = predecessors[j])
				stack[stackPos++] = j;
			while (stackPos != 0)
				cout << stack[--stackPos] << " ";
			cout << "\n";
		}
		else if (i < 10 && travelCosts[i] >= 10)
		{
			cout << i << "  | " << travelCosts[i] << " | ";
			for (j = i; j > -1; j = predecessors[j])
				stack[stackPos++] = j;
			while (stackPos != 0)
				cout << stack[--stackPos] << " ";
			cout << "\n";
		}
		else if (i < 10 && travelCosts[i] < 10)
		{
			cout << i << "  | " << travelCosts[i] << "  | ";
			for (j = i; j > -1; j = predecessors[j])
				stack[stackPos++] = j;
			while (stackPos != 0)
				cout << stack[--stackPos] << " ";
			cout << "\n";
		}
	}

	delete[] travelCosts, predecessors, qs, stack;
	delete graphPtr;
}

long long int Dijkstra::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return static_cast<long long int>(count.QuadPart);
}