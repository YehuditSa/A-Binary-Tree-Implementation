//Declaring a binary tree class and a BST class

#pragma once
#include <iostream>
#include "QueueVector.h"
using namespace std;

//-----------------------------------
//  class Tree (Binary Trees)
// process nodes in Pre/In/Post  order
//-----------------------------------

template <class T>
class Tree
{
protected:
	//--------------------------------------------------------
	//  inner class Node
	//		a single Node from a binary tree
	//--------------------------------------------------------
	class Node
	{
	public:
		Node* left;
		Node* right;
		Node* parent;
		T value;
		Node(T val) : value(val), left(NULL), right(NULL), parent(NULL) {}
		Node(T val, Node* l, Node* r) : value(val), left(l), right(r), parent(NULL) {}
		Node(T val, Node* p) : value(val), left(NULL), right(NULL), parent(p) {}               
	};		//end of Node class

	//data member of tree
	Node* root;

public:
	Tree() { root = NULL; }	 // initialize tree
	~Tree();
	int isEmpty() const;
	void clear() { clear(root); root = NULL; }
	void preOrder() { preOrder(root); }
	void inOrder() { inOrder(root); }
	void postOrder() { postOrder(root); }
	int height() const { return height(root); }
	void reflect() { reflect(root); }
	void breadthScan() const  { breadthScan(root); }

	virtual void process(T val) { cout << val << " "; }
	virtual void add(T val) = 0;
	virtual bool search(T val) = 0;
	virtual void remove(T val) = 0;


private:
	//private function for not give acsses to user
	void  clear(Node* current);
	void  preOrder(Node* current);
	void  inOrder(Node* current);
	void  postOrder(Node* current);
	int  height(Node* current) const;
	void  reflect(Node* current);
	void breadthScan(Node* current) const;

};



//----------------------------------------------------------
//  class Tree implementation
//----------------------------------------------------------
template <class T>
Tree<T>::~Tree() // deallocate tree
{
	if (root != NULL)
		clear(root);
}

//Calculating the height of the tree
template<class T>
int Tree<T>::height(Node* current) const 
{
	if (!current) 
		return -1;

	if (height(current->left) > height(current->right))
		return height(current->left)+1; 
	else
		return height(current->right)+1;
}

//Swapping between the children of each node in the tree
template <class T>
void Tree<T>::reflect(Node* current) 
{

	if (!current || !current->left && !current->right) //The stop condition
		return;

	reflect(current->left); //A recursive call - to the childrem of current
	reflect(current->right);

	Node* temp = current->left; //Swapping the two children
	current->left = current->right;
	current->right = temp;
}

//Printing the tree nodes in a transverse processing
template <class T>
void Tree<T>::breadthScan(Node* current) const
{

	if (!current) //The tree is empty
		return;

	QueueVector<Node*> queue(100); //Declaring an auxiliary queue

	queue.enqueue(current);
	while (!queue.isEmpty()) //There is still nodes in the queue
	{
		current = queue.dequeue(); //Printing the next node fron the queue
		cout << current->value<<" "; 
		if (current->left)  //If the last node has childrem - adding them to the queue
			queue.enqueue(current->left);
		if (current->right)
			queue.enqueue(current->right);
	}

}

template <class T>
void Tree<T>::clear(Node* current)
{
	if (current)
	{    // Release memory associated with children
		if (current->left)
			clear(current->left);
		if (current->right)
			clear(current->right);
		delete current;
	}
}

template <class T>
int Tree<T>::isEmpty() const
{
	return  root == NULL;
}

// preOrder processing of tree rooted at current
template <class T>
void Tree<T>::preOrder(Node* current)
{    // visit Node, left child, right child
	if (current)
	{   // process current Node
		process(current->value);
		// then visit children
		preOrder(current->left);
		preOrder(current->right);
	}
}

// inOrder processing of tree rooted at current
template <class T>
void Tree<T>::inOrder(Node* current)
{    // visit left child, Node, right child
	if (current)
	{
		inOrder(current->left);
		process(current->value);
		inOrder(current->right);
	}
}

// postOrder processing of tree rooted at current
template <class T>
void Tree<T>::postOrder(Node* current)
{    // visit left child, right child, node
	if (current)
	{
		postOrder(current->left);
		postOrder(current->right);
		process(current->value);
	}
}


