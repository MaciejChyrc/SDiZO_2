#pragma once
#include "GraphMatrix.h"
#include "GraphList.h"
#include "MinorStructs.h"

class Prim
{
private:
	static long long int read_QPC();
public:
	Prim();
	~Prim();
	static void primMatrix (int startV, GraphMatrix *graphMatrix, vector<double> vectorOfTimes);
	static void primList (int startV, GraphList *graphList, vector<double> vectorOfTimes);
};
