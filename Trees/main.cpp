#include "Tree.h"
#include "TreeIterator.h"
#include <string>
#include <iostream>
#include <queue>
#include "SFML/Graphics.hpp"
#include "XMLParser.h"
#include "utils.h"
#include "XMLValidator.h"
#include "TreeUtilities.h"

using namespace std;

//void to print the menu
void printMenu() {
	cout << "1. Display the Tree" << endl;
	cout << "2. Count the number of items in a folder" << endl;
	cout << "3. Determine the amount of memory used by a given folder" << endl;
	cout << "4. Prune the tree to remove empty folders" << endl;
	cout << "5. Find a given file/folder given a partial or complete filename" << endl;
	cout << "6. Display the contents of a given folder" << endl;
	cout << "7. Exit" << endl;
}

int main()
{
	XMLParser parser;
	XMLValidator validator;
	//C:\DSA Class\Test\xml_file.xml
	string filename;
	while (true) {
		//filename = utils::readString("Enter the name of the XML file: ");
		filename = "C:\\DSA Class\\Test\\xml_file.xml";
		bool isFileValid = validator.validateFile(filename);
		if (isFileValid) {
			break;
		}
		cout << "Invalid file, please try again.\n";
	}

	Tree<Folder*>* tree = parser.parseXML(filename);
	TreeIterator<Folder*> iter(tree);

	while (true) {
		printMenu();
		int choice = utils::readInt("Please enter your choice: ");

		switch (choice) {
		case 1: 
			cout << "Displaying the tree:\n";
			TreeUtilities::displayTree(iter, "->");
			break;

		case 2: {
			string folderName = utils::readString("Enter the name of the folder to count items in: ");
			TreeIterator<Folder*> folderIter = TreeUtilities::findFolder(iter, folderName);
			if (folderIter.node) {
				int itemCount = TreeUtilities::countItemsInFolder(folderIter);
				cout << "Number of items in '" << folderName << "': " << itemCount << endl;
			}
			else {
				cout << "Folder not found." << endl;
			}
			break;
		}

		case 3: {
			string folderName = utils::readString("Enter the name of the folder to determine memory usage: ");
			TreeIterator<Folder*> folderIter = TreeUtilities::findFolder(iter, folderName);
			if (folderIter.node) {
				double memoryUsed = TreeUtilities::memoryUsed(folderIter);
				cout << "Memory used by '" << folderName << "': " << memoryUsed << endl;
			}
			else {
				cout << "Folder not found." << endl;
			}
			break;
		}

		case 7:
			cout << "Exiting the program.\n";
			return 0;

		default:
			cout << "Invalid choice, please try again.\n";
			break;
		}
	}

	return 0;
}

