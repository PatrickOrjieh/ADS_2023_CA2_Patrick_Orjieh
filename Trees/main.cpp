#include "Tree.h"
#include "TreeIterator.h"
#include <string>
#include <iostream>
#include <queue>
#include "SFML/Graphics.hpp"
#include "XMLParser.h"
#include "utils.h"

using namespace std;

//void to print the menu
void printMenu() {
	cout << "1. Display the Tree" << endl;
	cout << "2. Count the number of items in a folder" << endl;
	cout << "3. Determine the amount of memory used by a given folder" << endl;
	cout << "4. Prune the tree to remove empty folders" << endl;
	cout << "5. Find a given file/folder given a partial or complete filename" << endl;
	cout << "6. Display the contents of a given folder" << endl;
}

int main()
{
	XMLParser parser;
	while (true) {
		string filename = "";
	}

	return 0;
}

