#include "MyQueue.h"
#include <iostream>


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

/*void MyQueue::push(Edge edge)
{
	resize(heapSize + 1);
	heap[heapSize - 1] = edge;
	for (int i = heapSize - 1; i >= 1; i--)
	{
		for (int j = heapSize - 1; j >= 1; j--)
		{
			if (heap[i].weight < heap[i - 1].weight) swap(i, i - 1);
		}
	}
}

void MyQueue::pop()
{
	if (heapSize > 0)
	{
		for (int i = 0; i < heapSize - 1; i++)
		{
			heap[i] = heap[i + 1];
		}
		resize(heapSize - 1);
	}
	else
	{
		std::cout << "Nie mozna usunac elementu. Kolejka jest pusta.\n";
	}
}*/

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
/*void MyQueue::push(Edge e)
{
	int i, j;

	i = heapSize++;                     // i ustawiamy na koniec kopca
	j = (i - 1) >> 1;               // Obliczamy pozycjê rodzica

									// Szukamy miejsca w kopcu dla e

	while (i && (heap[j].weight > e.weight))
	{
		heap[i] = heap[j];
		i = j;
		j = (i - 1) >> 1;
	}

	heap[i] = e;                    // KrawêdŸ e wstawiamy do kopca
}

// Usuwa korzeñ z kopca i odtwarza jego strukturê
//-----------------------------------------------
void MyQueue::pop()
{
	int i, j;
	Edge e;

	if (heapSize)
	{
		e = heap[--heapSize];

		i = 0;
		j = 1;

		while (j < heapSize)
		{
			if ((j + 1 < heapSize) && (heap[j + 1].weight < heap[j].weight)) j++;
			if (e.weight <= heap[j].weight) break;
			heap[i] = heap[j];
			i = j;
			j = (j << 1) + 1;
		}

		heap[i] = e;
	}
}*/

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

void MyQueue::print()
{
	for (int i = 0; i < heapSize; i++)
	{
		std::cout << heap[i].fromVertexId << heap[i].destVertexId << "\t";
	}
	std::cout << "\nIlosc elementow: " << heapSize << "\n";
}