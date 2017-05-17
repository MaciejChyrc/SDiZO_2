#include "MyQueue.h"
#include <iostream>

//akcesory prywatne i publiczne, konstruktor i destruktor
int MyQueue::leftSon(int index)
{
	return index * 2 + 1;
}

int MyQueue::rightSon(int index)
{
	return index * 2 + 2;
}

int MyQueue::parent(int index)
{
	return (index - 1) / 2;
}

MyQueue::MyQueue()
{
	heap = nullptr;
	heapSize = 0;
}

MyQueue::MyQueue(int size)
{
	heap = new Edge[size];
	heapSize = size;
}

MyQueue::~MyQueue()
{
	delete[] heap;
}

Edge MyQueue::front()
{
	return heap[0];
}
///<note>Dodanie krawedzi do kolejki
void MyQueue::push(Edge edge)
{
	resize(heapSize + 1);
	int i = heapSize - 1;
	int j = parent(i);

	while (i > 0 && heap[j].weight > edge.weight)
	{
		heap[i] = heap[j];
		i = j;
		j = parent(i);
	}
	heap[i] = edge;
}
///<note>Usuniecie krawedzi z kolejki
void MyQueue::pop()
{
	Edge edge;
	int i, j;

	if (heapSize > 2)
	{
		edge = heap[heapSize - 1];
		i = 0; j = 1;

		while (j < heapSize - 1)
		{
			if (rightSon(i) < heapSize - 1 && (heap[rightSon(i)].weight < heap[leftSon(i)].weight)) j++;
			if (edge.weight <= heap[j].weight) break;
			heap[i] = heap[j];
			i = j;
			j = leftSon(i);
		}
		heap[i] = edge;
		resize(heapSize - 1);
	}
	else if (heapSize == 2)
	{
		heap[0] = heap[1];
		resize(1);
	}
	else if (heapSize <= 1)
	{
		resize(0);
		std::cout << "Kolejka jest pusta. Nie ma czego usunac.\n";
	}
}
//-----------------------------------------------------------------------------
void MyQueue::resize(int newSize)
{
	try
	{
		Edge *temp = new Edge[newSize];
		//przepisanie calej tablicy i zostawienie pol dodanych niezainicjalizowanych (moga tam byc smieci)
		if (newSize > heapSize)
		{
			for (int i = 0; i < heapSize; i++)
			{
				temp[i] = heap[i];
			}
		}
		//przepisanie tablicy az do osiagniecia nowego rozmiaru (ostatnie elementy tracimy)
		else if (newSize < heapSize)
		{
			for (int i = 0; i < newSize; i++)
			{
				temp[i] = heap[i];
			}
		}
		delete[] heap;
		heap = temp;
		heapSize = newSize;
	}
	catch (std::bad_alloc)
	{
		std::cerr << "Nie udalo sie poprawnie zaalokowac kopca.\n";
	}
}
///<note>Wydruk zawartosci kolejki na ekran
void MyQueue::print()
{
	for (int i = 0; i < heapSize; i++)
	{
		std::cout << heap[i].fromVertexId << heap[i].destVertexId << "\t";
	}
	std::cout << "\nIlosc elementow: " << heapSize << "\n";
}