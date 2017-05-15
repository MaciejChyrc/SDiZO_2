#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <queue>
#include "MinorStructs.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Dijkstra.h"
#include "Prim.h"
#include <string>

using namespace std;

void readTextFile (string filepath, vector<Edge> &parEdges, GraphList *graphLU, GraphList *graphLD, GraphMatrix *graphMU, GraphMatrix *graphMD);
double averageOperationTime (const vector<double> vectorOfTimes);

/*int main ()
{
	GraphList *graphL = new GraphList();
	graphL->createRandomGraph(100, 50);
	cout << "Listowo:\n";
	for (int i = 0; i < graphL->listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphL->listOfEdges[i].weight << " " << graphL->listOfEdges[i].fromVertexId << " " << graphL->listOfEdges[i].destVertexId << "\n";
	}
	graphL->print();
	GraphMatrix *graphM = new GraphMatrix();
	graphM->createRandomGraph(100, 50);
	cout << "Macierzowo:\n";
	for (int i = 0; i < graphM->listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphM->listOfEdges[i].weight << " " << graphM->listOfEdges[i].fromVertexId << " " << graphM->listOfEdges[i].destVertexId << "\n";
	}
	graphM->print();
	Dijkstra* dijkstra = new Dijkstra ();
	dijkstra->dijkstraList(2, graphL);
	dijkstra->dijkstraMatrix(3, graphM);
	Prim* prim = new Prim ();
	prim->primList(4, graphL);
	prim->primMatrix(50, graphM);
	delete graphL, graphM, dijkstra, prim;
	system("PAUSE");
}*/
int main ()
{
	vector<double> dijkstraListTimes, dijkstraMatrixTimes, primListTimes, primMatrixTimes;
	GraphList *graphLU = new GraphList (), *graphLD = new GraphList ();
	GraphMatrix *graphMU = new GraphMatrix (), *graphMD = new GraphMatrix ();
	string filepath = "";
	char menuKey = 0;
	int cinValue = 0;

	do
	{
		cout << "\n---------------GLOWNE MENU---------------\n"
			<< "1. Wczytaj graf z pliku.\n"
			<< "2. Wyswietl graf macierzowo i listowo.\n"
			<< "3. Algorytm Prima.\n"
			<< "4. Algorytm Dijkstry.\n"
			<< "5. Zautomatyzowane testy czasowe.\n"
			<< "6. Zresetuj grafy.\n"
			<< "0. Wyjdz z programu.\n"
			<< "Wcisnij przycisk...\n";
		menuKey = _getch();
		switch (menuKey)
		{
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			break;
		}
	} while (menuKey != '0');

	delete graphLU, graphLD, graphMU, graphMD;
	return 0;
}

void readTextFile (string filepath, vector<Edge> &parEdges, GraphList *graphLU, GraphList *graphLD, GraphMatrix *graphMU, GraphMatrix *graphMD)
{
	ifstream file;
	file.open(filepath, ios::in);
	if (file.is_open())
	{
		Edge temp;
		int verticesNumber = 0, edgesNumber = 0, startVertex = 0, uselessPieceOfShit;
		file >> edgesNumber >> verticesNumber >> startVertex >> uselessPieceOfShit;
		if (file.fail()) cout << "Blad odczytu pierwszej linii pliku.\n";
		else
		{
			for (int i = 0; i < edgesNumber; i++)
			{
				file >> temp.fromVertexId >> temp.destVertexId >> temp.weight;
				if (file.fail())
				{
					cout << "Blad odczytu " << i + 2 << " linii pliku.\n";
					return;
				}
				else parEdges.push_back(temp);
			}
			graphLU->copyListOfEdges(parEdges);
			graphLD->copyListOfEdges(parEdges);
			graphMU->copyListOfEdges(parEdges);
			graphMD->copyListOfEdges(parEdges);
			graphLU->createGraphFromListOfEdges(verticesNumber);
			graphLD->createGraphFromListOfEdges(verticesNumber);
			graphMU->createGraphFromListOfEdges(verticesNumber);
			graphMD->createGraphFromListOfEdges(verticesNumber);
			graphLU->setStartVertex(startVertex);
			graphLD->setStartVertex(startVertex);
			graphMU->setStartVertex(startVertex);
			graphMD->setStartVertex(startVertex);
			file.close();
		}
	}
	else cout << "Blad otwarcia pliku.\n";
}

double averageOperationTime (const vector<double> vectorOfTimes)
{
	double averageTime = 0;
	for (int i = 0; i < vectorOfTimes.size(); i++)
	{
		averageTime += vectorOfTimes[i];
	}
	averageTime = averageTime / vectorOfTimes.size();

	return averageTime;
}