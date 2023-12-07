#pragma once
#include "Folder.h"
#include "Tree.h"
#include "DList.h"

class Dir : public Folder
{
private:
    DList<Tree<Folder*>*>* children;
public:
    Dir(std::string name);
    void addChild(Tree<Folder*>* child);
    //inherit count from Folder
    int count();
    ~Dir();
};

Dir::Dir(std::string name) : Folder(name)
{
	children = new DList<Tree<Folder*>*>(); 
}

void Dir::addChild(Tree<Folder*>* child) {
    children->append(child);
}

int Dir::count()
{
	int count = 1;
    DListIterator<Tree<Folder*>*> iter = children->getIterator();
    while (iter.isValid()) {
		count += iter.item()->count();
		iter.advance();
	}
	return count-1;
}

Dir::~Dir()
{
}