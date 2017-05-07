#pragma once
#include <list>

using namespace std;

struct Edge
{
	int weight, fromVertexId, destVertexId;

	Edge ()
	{
		weight = -1; fromVertexId = -1; destVertexId = -1;
	}

	Edge (int weight, int fromVertexId, int destVertexId)
	{
		this->weight = weight;
		this->fromVertexId = fromVertexId;
		this->destVertexId = destVertexId;
	}
};

struct Vertex
{
	int id;
	list<Edge> adjList;

	Vertex (int id) : id(id){}
};

struct ListElement
{
	ListElement* next;
	int weight, destVertexId;
};