//Yehudit Safrai 326050895
//Sadna b-C++
//Week9 Exe1
//Declaring a binary tree class and a BST class

/*In this file, I only changed the class to be a template class*/

#pragma once

#include <iostream>
using namespace std;

template<class T>
class Queue
{
public:
	virtual ~Queue() {};
	virtual void clear() = 0;
	virtual void enqueue(T value) = 0;
	virtual T dequeue() = 0;
	virtual T front() = 0;
	virtual bool isEmpty() const = 0;
};
