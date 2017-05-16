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
void graphListTests (GraphList *graphL, vector<double> &primTimes, vector<double> &dijkstraTimes);
void graphMatrixTests (GraphMatrix *graphM, vector<double> &primTimes, vector<double> &dijkstraTimes);
void saveTimesToTextFile (double avgPrim, double avgDijkstra, string size, string density);

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
	vector<Edge> vectorOfEdges;
	string filepath = "";
	char menuKey = 0, menuKeySecondary = 0;
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
			system("cls");
			cout << "Podaj sciezke wczytywanego pliku\n"
				<< "Na przyklad: C:\\\\Users\\\\User\\\\Documents\\\\textfile.txt\n"
				<< "Pamietaj o podwojnych backslashach jesli podajesz pelna sciezke!\n";
			cin >> filepath;
			readTextFile(filepath, vectorOfEdges, graphLU, graphLD, graphMU, graphMD);
			cout << "Zapisano grafy z pliku tekstowego.\n";
			break;
		case '2':
			system("cls");
			graphLU->print();
			graphMU->print();
			break;
		case '3':
			system("cls");
			cout << "\n-------------ALGORYTM PRIMA--------------\n"
				<< "1. Wyznacz minimalne drzewo rozpinajace grafu\n   w reprezentacji listowej.\n"
				<< "2. Wyznacz minimalne drzewo rozpinajace grafu\n   w reprezentacji macierzowej.\n"
				<< "9. Wroc do glownego menu.\n";
			menuKey = _getch();
			switch (menuKey)
			{
			case '1':
				break;
			case '2':
				break;
			case '0':
				menuKey = '9';
				break;
			default:
				break;
			}
			break;
		case '4':
			system("cls");
			cout << "\n------------ALGORYTM DIJKSTRY------------\n"
				<< "1. Wyznacz najkrotsze sciezki w grafie\n   w reprezentacji listowej.\n"
				<< "2. Wyznacz najkrotsze sciezki w grafie\n   w reprezentacji macierzowej.\n"
				<< "9. Wroc do glownego menu.\n";
			menuKey = _getch();
			switch (menuKey)
			{
			case '1':
				break;
			case '2':
				break;
			case '0':
				menuKey = '9';
				break;
			default:
				break;
			}
			break;
		case '5':
			system("cls");
			cout << "\n---------------TRYB TESTOWY--------------\n"
				<< "1. Przeprowadz testy dla reprezentacji listowej.\n"
				<< "2. Przeprowadz testy dla reprezentacji macierzowej.\n"
				<< "9. Wroc do glownego menu.\n";
			menuKey = _getch();
			switch (menuKey)
			{
			case '1':
				do
				{
					cout << "Na pewno chcesz przeprowadzic testy?\nMoze to chwilke zajac. (y/n)\n";
					menuKeySecondary = _getch();
					if (menuKeySecondary == 'y' || menuKeySecondary == 'Y')
					{
						graphListTests(graphLU, primListTimes, dijkstraListTimes);
					}
				} while (menuKeySecondary != 'y' && menuKeySecondary != 'Y' && menuKeySecondary != 'n' && menuKeySecondary != 'N');
				break;
			case '2':
				do
				{
					cout << "Na pewno chcesz przeprowadzic testy?\nMoze to chwilke zajac. (y/n)\n";
					menuKeySecondary = _getch();
					if (menuKeySecondary == 'y' || menuKeySecondary == 'Y')
					{
						graphMatrixTests(graphMU, primMatrixTimes, dijkstraMatrixTimes);
					}
				} while (menuKeySecondary != 'y' && menuKeySecondary != 'Y' && menuKeySecondary != 'n' && menuKeySecondary != 'N');
				break;
			case '0':
				menuKey = '9';
				break;
			default:
				break;
			}
			break;
		case '6':
			delete graphLU, graphLD, graphMU, graphMD;
			graphLU = new GraphList ();
			graphLD = new GraphList ();
			graphMU = new GraphMatrix ();
			graphMD = new GraphMatrix ();
			cout << "Zresetowano grafy.\n";
			break;
		default:
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

void graphListTests (GraphList *graphL, vector<double> &primTimes, vector<double> &dijkstraTimes)
{
	int graphVerticesNumber = 60, graphDensity = 25;
	
	while (graphVerticesNumber <= 140)
	{
		delete graphL;
		graphL = new GraphList ();
		graphL->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primList(0, graphL, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraList(0, graphL, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 50;

	while (graphVerticesNumber <= 140)
	{
		delete graphL;
		graphL = new GraphList ();
		graphL->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primList(0, graphL, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraList(0, graphL, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 75;

	while (graphVerticesNumber <= 140)
	{
		delete graphL;
		graphL = new GraphList ();
		graphL->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primList(0, graphL, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraList(0, graphL, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 99;

	while (graphVerticesNumber <= 140)
	{
		delete graphL;
		graphL = new GraphList ();
		graphL->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primList(0, graphL, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraList(0, graphL, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	cout << "Zakonczono test.\n";
}

void graphMatrixTests (GraphMatrix *graphM, vector<double> &primTimes, vector<double> &dijkstraTimes)
{
	int graphVerticesNumber = 60, graphDensity = 25;

	while (graphVerticesNumber <= 140)
	{
		delete graphM;
		graphM = new GraphMatrix ();
		graphM->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primMatrix(0, graphM, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraMatrix(0, graphM, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 50;

	while (graphVerticesNumber <= 140)
	{
		delete graphM;
		graphM = new GraphMatrix ();
		graphM->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primMatrix(0, graphM, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraMatrix(0, graphM, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 75;

	while (graphVerticesNumber <= 140)
	{
		delete graphM;
		graphM = new GraphMatrix ();
		graphM->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primMatrix(0, graphM, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraMatrix(0, graphM, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	graphVerticesNumber = 60, graphDensity = 99;

	while (graphVerticesNumber <= 140)
	{
		delete graphM;
		graphM = new GraphMatrix ();
		graphM->createRandomGraph(graphVerticesNumber, graphDensity);

		for (int i = 0; i < 100; i++)
		{
			cout << "Testy algorytmu Prima.\n";
			Prim::primMatrix(0, graphM, primTimes);
			cout << "Testy algorytmu Dijkstry.\n";
			Dijkstra::dijkstraMatrix(0, graphM, dijkstraTimes);
		}
		saveTimesToTextFile(averageOperationTime(primTimes), averageOperationTime(dijkstraTimes), std::to_string(graphVerticesNumber), std::to_string(graphDensity));
		primTimes.clear();
		dijkstraTimes.clear();
		graphVerticesNumber += 20;
	}
	cout << "Zakonczono test.\n";
}

void saveTimesToTextFile (double avgPrim, double avgDijkstra, string size, string density)
{
	string graphSizeAndDensity = size + "_" + density;
	//cout << "Podaj rozmiar grafu i gestosc jako nazwe pliku (na przyklad: 100_50): \n";
	//cin >> graphSizeAndDensity;

	std::ofstream file;
	file.open("c:\\users\\szatan\\desktop\\graf" + graphSizeAndDensity + ".txt", std::ios::out);

	if (file.is_open())
	{
		file << "Prim, Dijkstra\n";
		if (file.fail()) std::cerr << "Blad zapisu.\n";
		else
		{
			file << avgPrim << ", " << avgDijkstra;
			if (file.fail()) std::cerr << "Blad zapisu.\n";
		}
		file.close();
	}
	else std::cerr << "Blad otwarcia pliku.\n";
}