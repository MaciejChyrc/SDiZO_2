#pragma once
#include "GraphList.h"
#include "GraphMatrix.h"

class Dijkstra
{
private:
	static long long int read_QPC();
public:
	Dijkstra ();
	~Dijkstra ();
	static void dijkstraMatrix (int startV, GraphMatrix *graphMatrix, vector<double> vectorOfTimes);
	static void dijkstraList (int startV, GraphList *graphList, vector<double> vectorOfTimes);
};