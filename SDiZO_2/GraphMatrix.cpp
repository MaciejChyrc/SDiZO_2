#include "GraphMatrix.h"
#include <iostream>
#include <ctime>


GraphMatrix::GraphMatrix()
{
	matrix = nullptr;
	verticesNumber = 0;
	edgesNumber = 0;
}

GraphMatrix::~GraphMatrix()
{
	for (int i = 0; i < verticesNumber; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int GraphMatrix::getVerticesNumber()
{
	return verticesNumber;
}

int ** GraphMatrix::getMatrix()
{
	return matrix;
}

void GraphMatrix::createGraph(int v)
{
	matrix = new int*[v];
	verticesNumber = v;
	edgesNumber = listOfEdges.size();
	vector<Edge> tempListOfEdges = listOfEdges;

	for (int i = 0; i < v; i++)
	{
		matrix[i] = new int[v];
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			matrix[i][j] = INT_MAX;
		}
	}
	while (!tempListOfEdges.empty())
	{
		matrix[tempListOfEdges.back().fromVertexId][tempListOfEdges.back().destVertexId] = tempListOfEdges.back().weight;
		matrix[tempListOfEdges.back().destVertexId][tempListOfEdges.back().fromVertexId] = tempListOfEdges.back().weight;
		tempListOfEdges.pop_back();
	}
}

void GraphMatrix::createRandomGraph(int v, int fillPercent)
{
	if (fillPercent > 99 || fillPercent < 25)
	{
		cout << "Nieprawidlowy wspolczynnik gestosci grafu.\n";
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
	matrix = new int*[v];
	verticesNumber = v;
	edgesNumber = edgesToCreate;

	for (int i = 0; i < v; i++)
	{
		matrix[i] = new int[v];
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			matrix[i][j] = INT_MAX;
		}
	}

	int v1, v2, w;
	Edge* edge = nullptr;
	//tworzymy najpierw drzewo aby byc pewnym ze graf jest spojny
	for (int i = 0; i < v - 1; i++, edgesToCreate--)
	{		
		v2 = i + 1;/*rand() % v;*/
		w = rand() % 10 + 1;
		//while (v2 == i || matrix[i][v2] != INT_MAX) v2 = rand() % v;
		matrix[i][v2] = w;
		matrix[v2][i] = w;
		edge = new Edge (w, i, v2);
		listOfEdges.push_back(*edge);
	}
	//nastepnie reszta krawedzi jest generowana losowo
	for (int i = 0; i < edgesToCreate; i++)
	{
		v1 = rand() % v;
		v2 = rand() % v;
		w = rand() % 10 + 1;
		while (v1 == v2 || matrix[v1][v2] != INT_MAX)
		{
			v1 = rand() % v;
			v2 = rand() % v;
		}
		matrix[v1][v2] = w;
		matrix[v2][v1] = w;
		edge = new Edge (w, v1, v2);
		listOfEdges.push_back(*edge);
	}
	delete edge;
}
//dodajemy do klasy liste krawedzi wczytana poza klasa (np. z pliku)
void GraphMatrix::copyListOfEdges(vector<Edge> par)
{
	listOfEdges = par;
}

void GraphMatrix::print()
{
	cout << "Reprezentacja macierzowa:\n";
	for (int i = 0; i < verticesNumber; i++)
	{
		for (int j = 0; j < verticesNumber; j++)
		{
			if (matrix[i][j] == INT_MAX) cout << "x  ";
			else if (matrix[i][j] < 10) cout << matrix[i][j] << "  ";
			else cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}