#pragma once
#include "MinorStructs.h"
//kopiec z 1 projektu zaadaptowany do sluzenia jako kolejka priorytetowa i
//obslugiwania krawedzi grafow i okrojony z niepotrzebnych rzeczy
class MyQueue
{
private:
	Edge* heap;
	int heapSize;
	int leftSon (int index);
	int rightSon (int index);
	int parent (int index);
public:
	MyQueue ();
	MyQueue (int size);
	~MyQueue ();
	Edge front ();
	void push (Edge edge);
	void pop ();
	void resize (int newSize);
	void print ();
};