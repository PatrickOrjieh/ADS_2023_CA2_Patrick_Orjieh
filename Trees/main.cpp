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
#include "DirectoryVisual.h"

using namespace std;

//void to print the menu
void printMenu() {
	cout << "1. Display the Tree" << endl;
	cout << "2. Count the number of items in a folder" << endl;
	cout << "3. Determine the amount of memory used by a given folder" << endl;
	cout << "4. Prune the tree to remove empty folders" << endl;
	cout << "5. Find a given file/folder given a partial or complete filename" << endl;
	cout << "6. Display the contents of a given folder" << endl;
	cout << "7. Run SFML Graphics" << endl;
	cout << "8. Exit the program" << endl;
}

int main()
{
	XMLParser parser;
	XMLValidator validator;
	string filename;
	while (true) {
		//filename = utils::readString("Enter the name of the XML file: ");
		filename = "xml_files/xml_file.xml";
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

		case 4:
			cout << "Pruning the tree to remove empty folders.\n";
			TreeUtilities::pruneEmptyDirectories(tree);
			break;

		case 5: {
			cout << "Finding a given file/folder given a partial or complete filename.\n";
			string name = utils::readString("Enter the name of the file/folder to find: ");
			string path = TreeUtilities::findPath(iter, name);
			if (path != "") {
				cout << "Path to '" << name << "': " << path << endl;
			}
			else {
				cout << "File/folder not found." << endl;
			}
			break;
		}

		case 6: {
			cout << "Displaying the contents of a given folder.\n";
			string folderName = utils::readString("Enter the name of the folder to display contents of: ");
			TreeIterator<Folder*> folderIter = TreeUtilities::findFolder(iter, folderName);
			if (folderIter.node) {
				TreeUtilities::displayFolderContents(folderIter);
			}
			else {
				cout << "Folder not found." << endl;
			}
			break;
		}

		case 7: {
			cout << "Running SFML Graphics.\n";

			sf::RenderWindow window(sf::VideoMode(800, 600), "Directory Browser");
			DirectoryVisual rootDirectoryVisual(tree, sf::Vector2f(100, 100));

			while (window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();
				rootDirectoryVisual.draw(window);
				window.display();
			}
			break;
		}

		case 8:
			cout << "Exiting the program.\n";
			return 0;

		default:
			cout << "Invalid choice, please try again.\n";
			break;
		}
	}

	return 0;
}

