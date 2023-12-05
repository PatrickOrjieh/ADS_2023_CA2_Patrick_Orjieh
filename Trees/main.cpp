// Trees.cpp : Defines the entry point for the console application.
//
#include "Tree.h"
#include "TreeIterator.h"
#include <string>
#include <iostream>
#include <queue>
#include "SFML/Graphics.hpp"

using namespace std;
/*
	The indented parenthetic representation of a tre
*/
//void displayTree(TreeIterator<string> iter, string indent)
//{
//	cout << indent << iter.item() << endl;
//	if (iter.childValid()){
//		
//		while (iter.childValid())
//		{
//			iter.down();
//			displayTree(iter, indent + "  ");
//			iter.up();
//			iter.childForth();
//			
//		}
//		
//	}
//	cout << indent << "end" << endl;
//}

template <class T>
void displayTree(TreeIterator<T> iter, string indent)
{
	cout << indent << iter.node->data;
	if (iter.childValid())
	{
		cout << "(" << endl;
		while (iter.childValid())
		{
			TreeIterator<T> iter2(iter.childIter.item());
			displayTree(iter2, " \t " + indent + "  ");
			iter.childForth();
		}
		cout << indent << ")" << endl;
	}
	cout << endl;
}

/*
	Print using a Depth First Search
*/
template <class T>
void printDFS(TreeIterator<T> iter)
{
	cout << iter.item() << "->";
	if (iter.childValid())
	{
		while (iter.childValid())
		{
			TreeIterator<T> iter2(iter.childIter.item());
			printDFS(iter2);
			iter.childForth();

		}
	}
}
/*
	Print using a Breadth first Search
*/
template <class T>
void printBFS(Tree<T>* tree)
{
	queue<Tree<T>*> q;
	q.push(tree);
	while (!q.empty())
	{
		Tree<T>* node = q.front();
		cout << node->data << "->";
		DListIterator<Tree<T>*> iter = node->children->getIterator();
		while (iter.isValid())
		{
			q.push(iter.item());
			iter.advance();
		}
		q.pop();
	}
}
/*
	Code to test for question 1
*/
void question1()
{
	Tree<string>* root = new Tree<string>("Sales");
	TreeIterator<string> iter(root);
	iter.appendChild("Domestic");
	iter.appendChild("International");
	iter.childEnd();
	iter.down();
	iter.appendChild("Canada");
	iter.appendChild("South America");
	iter.appendChild("Overseas");
	iter.childEnd();
	iter.down();
	iter.appendChild("Africa");
	iter.appendChild("Europe");
	iter.appendChild("Asia");
	iter.appendChild("Australia");
	iter.root();
	displayTree(iter, "->");
	delete root;
	root = nullptr;
}
/*
	Code to test question 2 & 3.
*/
void question2()
{
	Tree<int>* root = new Tree<int>(0);
	TreeIterator<int> iter(root);
	iter.appendChild(1);
	iter.appendChild(4);
	iter.appendChild(6);
	iter.down();
	iter.appendChild(2);
	iter.appendChild(3);
	iter.up();
	iter.childForth();
	iter.down();
	iter.appendChild(5);
	iter.up();
	iter.childEnd();
	iter.down();
	iter.appendChild(7);
	iter.appendChild(8);
	iter.root();
	//displayTree(iter, "->");
	printDFS(iter);
	cout << endl;
	printBFS(root);
	delete root;
	root = nullptr;
}

int main()
{

	//question1();
	question2();

	return 0;
}

