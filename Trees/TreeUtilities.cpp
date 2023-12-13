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

TreeIterator<Folder*> TreeUtilities::findFolder(TreeIterator<Folder*> iter, const std::string& folderName) {
    if (iter.item() && iter.item()->getName() == folderName) {
        return iter;
    }
    if (iter.childValid()) {
        iter.childStart();
        while (iter.childValid()) {
            TreeIterator<Folder*> foundIter = findFolder(iter.childIter.item(), folderName);
            if (foundIter.node) {
                return foundIter;
            }
            iter.childForth();
        }
    }
    return TreeIterator<Folder*>(nullptr);
}

int TreeUtilities::countItemsInFolder(TreeIterator<Folder*> folderIter) {
    int count = 0;
    if (folderIter.childValid()) {
        folderIter.childStart();
        while (folderIter.childValid()) {
            count++;
            folderIter.childForth();
        }
    }
    return count;
}

double TreeUtilities::memoryUsed(TreeIterator<Folder*> iter) {
    if (!iter.node) return 0.0;

    std::queue<Tree<Folder*>*> q;
    q.push(iter.node);
    double totalMemory = 0.0;

    while (!q.empty()) {
        Tree<Folder*>* currentNode = q.front();
        q.pop();

        // Get all children of the directory
        if (currentNode->children) {
            DListIterator<Tree<Folder*>*> childIter = currentNode->children->getIterator();
            while (childIter.isValid()) {
                q.push(childIter.item());
                childIter.advance();
            }
        }

        // Process the file and add up memory
        File* file = dynamic_cast<File*>(currentNode->getData());
        if (file) {
            std::string lengthStr = file->getLength();
            size_t lastCharPos = lengthStr.find_last_not_of("0123456789.");
            double value = std::stod(lengthStr.substr(0, lastCharPos));
            std::string unit = lengthStr.substr(lastCharPos);
            if (unit == "b") {
                totalMemory += value;
            }
        }
    }

    return totalMemory;
}

void TreeUtilities::pruneEmptyDirectories(Tree<Folder*>* node) {
    if (!node) return;

    DListIterator<Tree<Folder*>*> iter = node->children->getIterator();

    while (iter.isValid()) {
        Tree<Folder*>* child = iter.item();

        pruneEmptyDirectories(child);

        Dir* dir = dynamic_cast<Dir*>(child->getData());
        if (dir && child->children->isEmpty()) {
            delete child;
            iter = node->children->remove(iter);
        }
        else {
            iter.advance();
        }
    }
}


void TreeUtilities::displayFolderContents(TreeIterator<Folder*> iter) {

}