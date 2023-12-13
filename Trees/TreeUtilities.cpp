#include "TreeUtilities.h"
#include <iostream>

void TreeUtilities::displayTree(TreeIterator<Folder*> iter, const std::string& indent) {
    Folder* folder = iter.node->data;

    // to cast to Dir* and File*
    Dir* dir = dynamic_cast<Dir*>(folder);
    File* file = dynamic_cast<File*>(folder);

    if (dir) {
        std::cout << indent << "Directory: " << dir->getName() << std::endl;
    }
    else if (file) {
        std::cout << indent << "File: " << file->getName() << " (" << file->getLength() << ", " << file->getType() << ")" << std::endl;
    }

    if (iter.childValid()) {
        std::cout << indent << "(" << std::endl;
        while (iter.childValid()) {
            TreeIterator<Folder*> childIter(iter.childIter.item());
            displayTree(childIter, "\t" + indent);
            iter.childForth();
        }
        std::cout << indent << ")" << std::endl;
    }
}

int TreeUtilities::countItems(TreeIterator<Folder*> iter) {
	return 0;
}

double TreeUtilities::memoryUsed(TreeIterator<Folder*> iter) {
	return 0.0;
}

void TreeUtilities::pruneTree(TreeIterator<Folder*> iter) {

}

std::string TreeUtilities::findFolder(TreeIterator<Folder*> iter, const std::string& filename) {
	return std::string();
}

void TreeUtilities::displayFolderContents(TreeIterator<Folder*> iter) {

}