#pragma once
#include "Folder.h"
#include "Tree.h"
#include "DList.h"
#include "DListIterator.h"
#include "TreeIterator.h"

class Dir : public Folder
{
private:
    DList<Tree<Folder*>*>* children;
public:
    Dir(std::string name);
    void addChild(Tree<Folder*>* child);
    int count();
    bool removeChild(const std::string& childName);
    ~Dir();
};

Dir::Dir(std::string name) : Folder(name)
{
	children = new DList<Tree<Folder*>*>(); 
}

void Dir::addChild(Tree<Folder*>* child) {
    children->append(child);
}

int Dir::count() {
    int count = 0;
    DListIterator<Tree<Folder*>*> iter = children->getIterator();
    while (iter.isValid()) {
        count += iter.item()->count();
        iter.advance();
    }
    return count;
}

bool Dir::removeChild(const std::string& childName) {
    DListIterator<Tree<Folder*>*> iter = children->getIterator();
    while (iter.isValid()) {
        if (iter.item()->getData()->getName() == childName) {
			children->remove(iter);
			return true;
		}
		iter.advance();
	}
	return false;
}

Dir::~Dir()
{
}