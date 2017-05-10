#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include "MinorStructs.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Dijkstra.h";
#include <string>

using namespace std;

void readTextFile (string filepath, vector<Edge> &parEdges, GraphList *graphLU, GraphList *graphLD, GraphMatrix *graphMU, GraphMatrix *graphMD);

int main ()
{
	/*vector<Edge> edges;
	Edge edge;
	edge.weight = 3; edge.fromVertexId = 0; edge.destVertexId = 1;
	edges.push_back(edge);
	edge.weight = 1; edge.fromVertexId = 1; edge.destVertexId = 2;
	edges.push_back(edge);
	edge.weight = 2; edge.fromVertexId = 2; edge.destVertexId = 0;
	edges.push_back(edge);
	edge.weight = 6; edge.fromVertexId = 3; edge.destVertexId = 1;
	edges.push_back(edge);
	edge.weight = 5; edge.fromVertexId = 2; edge.destVertexId = 3;
	edges.push_back(edge);
	edge.weight = 8; edge.fromVertexId = 0; edge.destVertexId = 4;
	edges.push_back(edge);
	for (int i = 0; i < edges.size(); i++)
	{
		cout << edges[i].weight << edges[i].fromVertexId << edges[i].destVertexId << "\n";
	}
	GraphList *graphL = new GraphList();
	graphL->copyListOfEdges(edges);
	graphL->createGraphFromListOfEdges(5);*/
	GraphList *graphL = new GraphList();
	graphL->createRandomGraph(10, 90);
	cout << "Listowo:\n";
	for (int i = 0; i < graphL->listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphL->listOfEdges[i].weight << " " << graphL->listOfEdges[i].fromVertexId << " " << graphL->listOfEdges[i].destVertexId << "\n";
	}
	graphL->print();
	GraphMatrix *graphM = new GraphMatrix();
	//graphM.copyListOfEdges(edges);
	//graphM.createGraphFromListOfEdges(3);
	graphM->createRandomGraph(15, 25);
	cout << "Macierzowo:\n";
	for (int i = 0; i < graphM->listOfEdges.size(); i++)
	{
		cout << "Krawedz " << i << ": " << graphM->listOfEdges[i].weight << " " << graphM->listOfEdges[i].fromVertexId << " " << graphM->listOfEdges[i].destVertexId << "\n";
	}
	graphM->print();
	Dijkstra* dijkstra = new Dijkstra ();
	dijkstra->dijkstraList(2, graphL);
	dijkstra->dijkstraMatrix(3, graphM);
	delete graphL, graphM, dijkstra;
	system("PAUSE");
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