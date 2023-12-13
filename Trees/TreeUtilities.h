#pragma once
#include "Tree.h"
#include "TreeIterator.h"
#include "Dir.h"
#include "File.h"
#include <string>
#include <queue>

class TreeUtilities {
public:
	//display contents of tree
	static void displayTree(TreeIterator<Folder*> iter, const std::string& indent);

	// Finds the folder with the specified name and returns an iterator to it
	static TreeIterator<Folder*> findFolder(TreeIterator<Folder*> iter, const std::string& folderName);

	// Counts the number of items (files or folders) within the folder that the iterator points to
	static int countItemsInFolder(TreeIterator<Folder*> folderIter);

	//determine the amount of memory used by a given folder
	static double memoryUsed(TreeIterator<Folder*> iter);

	//prune the tree to remove empty folders
	static void pruneTree(TreeIterator<Folder*> iter);

	//find a given file/folder given a partial or complete filename and generate the path for the given file/folder
	//static std::string findFolder(TreeIterator<Folder*> iter, const std::string& filename);

	//display the contents of a given folder
	static void displayFolderContents(TreeIterator<Folder*> iter);
};
