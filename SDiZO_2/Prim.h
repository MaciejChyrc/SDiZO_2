#pragma once
#include "GraphMatrix.h"
#include "GraphList.h"
#include "MinorStructs.h"

class Prim
{
public:
	Prim();
	~Prim();
	void primMatrix (int startV, GraphMatrix *graphMatrix);
	void primList (int startV, GraphList *graphList);
};
