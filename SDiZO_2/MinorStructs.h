#pragma once

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

struct ListElement
{
	ListElement* next;
	int weight, destVertexId;
};