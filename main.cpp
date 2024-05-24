//Declaring a binary tree class and a BST class

#include <iostream>
#include "SearchTree.h"
using namespace std;

enum { END, ADD, SEARCH, REMOVE, BREADTHSCAN, HEIGHT, SUCCESSOR, DELETEDUP, REFLECT };

int main()
{
	SearchTree<int> T1;
	cout << "enter 10 numbers:\n";
	int x, y, z;
	for (int i = 0; i < 10; i++)
	{
		cin >> x;
		T1.add(x);
	}
	cout << "inorder: ";
	T1.inOrder();
	cout << "\nenter 0-8:\n";
	cin >> x;
	while (x != END)
	{
		switch (x)
		{
		case ADD: cout << "enter a number: ";
			cin >> y;
			T1.add(y);
			cout << "after adding " << y << ": ";
			T1.inOrder();
			cout << endl;
			break;
		case SEARCH: cout << "enter a number: ";
			cin >> y;
			if (T1.search(y))
				cout << "exist" << endl;
			else
				cout << "does not exist" << endl;
			break;
		case REMOVE:cout << "enter a number: ";
			cin >> y;
			try
			{
				T1.remove(y);
				cout << "after removing " << y << ": ";
				T1.inOrder();
				cout << endl;
			}
			catch (const char* str)
			{
				cout << str << endl;
			}
			break;
		case BREADTHSCAN: cout << "breadth first scan: ";
			T1.breadthScan();
			cout << endl;
			break;
		case HEIGHT:cout << "height of tree: " << T1.height() << endl;
			break;
		case SUCCESSOR:cout << "enter a number: ";
			cin >> y;
			try
			{
				z = T1.successor(y);
				cout << "successor of " << y << " is: " << z << endl;

			}
			catch (const char* str)
			{
				cout << str << endl;
			}
			break;
		case DELETEDUP: cout << "after deleting duplicates: ";
			T1.deleteDuplicates();
			T1.inOrder();
			cout << endl;
			break;
		case REFLECT:
			T1.reflect();
			cout << "reflected tree: ";
			T1.inOrder();
			T1.reflect();
			cout << endl;
			break;
		}
		cout << "enter 0-8:\n";
		cin >> x;
	}
	return 0;
}

/*
enter 10 numbers:
 1 2 3 9 8 7 1 5 9 7
inorder: 1 1 2 3 5 7 7 8 9 9
enter 0-8:
1
enter a number: 4
after adding 4: 1 1 2 3 4 5 7 7 8 9 9
enter 0-8:
2
enter a number: 7
exist
enter 0-8:
2
enter a number: 10
does not exist
enter 0-8:
3
enter a number: 5
after removing 5: 1 1 2 3 4 7 7 8 9 9
enter 0-8:
4
breadth first scan: 1 1 2 3 9 8 7 9 7 4
enter 0-8:
5
height of tree: 7
enter 0-8:
6
enter a number: 8
successor of 8 is: 9
enter 0-8:
6
enter a number: 9
no successor
enter 0-8:
7
after deleting duplicates: 1 2 3 4 7 8 9
enter 0-8:
8
reflected tree: 9 8 7 4 3 2 1
enter 0-8:
0

C:\C++\SadnaC++\Week9\YehuditSafraiWeek9Exe1\x64\Debug\YehuditSafraiWeek9Exe1.exe (process 28632) exited with code 0.
Press any key to close this window . . .
*/
