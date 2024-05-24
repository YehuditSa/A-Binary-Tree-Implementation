//Declaring a binary tree class and a BST class

#pragma once
#include "Tree.h"
#include <iostream>
using namespace std;

template<class T>
class SearchTree : public Tree<T>
{

public:
	void add(T value);
	bool search(T value) { return search(Tree<T>::root, value); }
	void remove(T val);
	T successor(T val) { return successor(searchNode(Tree<T>::root, val))->value; }
	void deleteDuplicates() { deleteDuplicates(Tree<T>::root); }

private:

	void add(typename Tree<T>::Node* current, T val);
	bool search(typename Tree<T>::Node* current, T val);
	void remove(typename Tree<T>::Node* current, T val);
	typename Tree<T>::Node* successor(typename Tree<T>::Node* current);
	typename Tree<T>::Node* minimum(typename Tree<T>::Node* current);
	typename Tree<T>::Node* searchNode(typename Tree<T>::Node* current, T val);
	void deleteDuplicates(typename Tree<T>::Node* current);
};



template <class T>
void SearchTree<T>::add(T val)
{
	// add value to binary search tree 
	if (!Tree<T>::root)
	{
		Tree<T>::root = new typename Tree<T>::Node(val);
		return;
	}
	add(Tree<T>::root, val);
}

//Removing a value from a binary search tree 
template<class T>
void SearchTree<T>::remove(T val)
{

	if (Tree<T>::root->value == val) //The node to be removed is the root
	{
		if (!Tree<T>::root->left && !Tree<T>::root->right) //The node has no children - the tree has only a node
		{
			Tree<T>::root = nullptr; 
			delete Tree<T>::root;
		}
		else if (Tree<T>::root->left && !Tree<T>::root->right) //The node has only a child - the left
		{
			typename Tree<T>::Node* temp = Tree<T>::root; //The new root is the left child of the old root
			Tree<T>::root = Tree<T>::root->left;
			Tree<T>::root->parent = nullptr;
			delete temp;
		}
		else if (!Tree<T>::root->left && Tree<T>::root->right) //The node has only a child - the right
		{
			typename Tree<T>::Node* temp = Tree<T>::root; //The new root is the right child of the old root
			Tree<T>::root = Tree<T>::root->right;
			Tree<T>::root->parent = nullptr;
			delete temp;
		}
		else //The node has 2 children
			remove(Tree<T>::root, val); 

	}
	else //The node to be removed is not the root
		remove(Tree<T>::root, val);
}



template <class T>
void SearchTree<T>::add(typename Tree<T>::Node* current, T val)
{
	if (current->value < val)
	{
		if (!current->right)
		{
			current->right = new typename Tree<T>::Node(val, current);
			return;
		}
		else
			add(current->right, val);

	}
	else
	{
		if (!current->left)
		{
			current->left = new typename Tree<T>::Node(val, current);
			return;
		}
		else
			add(current->left, val);
	}
}

template <class T>
bool SearchTree<T>::search(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		return false;	// not found
	if (current->value == val)
		return true;
	if (current->value < val)
		return search(current->right, val);
	else
		return search(current->left, val);
}

//Removing a value from a recieved binary search tree 
template <class T>
void SearchTree<T>::remove(typename Tree<T>::Node* current, T val)
{

	current = searchNode(current, val); //Finding the node to be removed

	if (!current->left && !current->right) //The node has no children
	{
		if (current->parent->right == current) //The node parent will point to nullptr
			current->parent->right = nullptr;
		else 
			current->parent->left = nullptr;
		delete current;
	}
	else if (current->left && !current->right) //The node has only a child - the left
	{
		if (current->parent->right == current)  //The node parent will point to the node child
			current->parent->right = current->left;
		else
			current->parent->left = current->left;
		delete current;
	}
	else if (current->right && !current->left) //The node has only a child - the right
	{
		if (current->parent->right == current) //The node parent will point to the node child
			current->parent->right = current->right;
		else
			current->parent->left = current->right;
		delete current;
	}
	else //The node has 2 children
	{
		typename Tree<T>::Node* mySuccessor = successor(current); //Switching between the node and its successor
		T temp = mySuccessor->value;
		mySuccessor->value = current->value;
		current->value = temp;
		remove(mySuccessor, mySuccessor->value); //Removing the old successor = the node
	}
}

//Finding the node that contains the next number after the received number 
template <class T>
typename Tree<T>::Node* SearchTree<T>::successor(typename Tree<T>::Node* current)
{
	if (!current->right && !current->parent)  //The node is the root, and it doesn't have a right child
		throw "no successor";

	if (current->right)  //The successor is the minimal number in the right child
		return minimum(current->right);

	//The node doesn't have a right child
	typename Tree<T>::Node* parent = current->parent; 
	while (parent && current == parent->right) //Climbing until it becomes clear that we are on the left branch of a parent
	{
		current = parent;
		parent = current->parent;
	}
	if(!parent) //The found parent is nullptr - the node is the maximal node in the tree
		throw "no successor";

	return parent; //Returning the found parent
}


//Finding the minimal node in a recieved tree
template <class T>
typename Tree<T>::Node* SearchTree<T>::minimum(typename Tree<T>::Node* current)
{
	//The minimal number is the leftmost node
	if (!current->left)
		return current;
	return minimum(current->left);
}

//Returning a pointer to the node that contains the recieved value
template<class T>
typename Tree<T>::Node* SearchTree<T>::searchNode(typename Tree<T>::Node* current, T val)
{
	if (!current) //The stop condition
		return nullptr;
	if (current->value == val) //The node is found
		return current;
	if (current->value < val) //a recursive call - searching the node in the current tree children
		return searchNode(current->right, val);
	else
		return searchNode(current->left, val);
}

//Deleting duplicate values from the tree
template<class T>
void SearchTree<T>::deleteDuplicates(typename Tree<T>::Node* current)
{
	if (!current) //The stop condition
		return;
	if (search(current->left, current->value)) //In the left child there is a node that is identical to the root
	{
		deleteDuplicates(current->left); //a recursive call to the left child of the current tree
		remove(current->left, current->value); //Deleting the redundant node

	}
	
	deleteDuplicates(current->right); //Recursive calls to the children of the current tree
	deleteDuplicates(current->left);


}
