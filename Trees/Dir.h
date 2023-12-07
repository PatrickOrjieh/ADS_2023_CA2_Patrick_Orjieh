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
	int count = 0;
	return count;
}

Dir::~Dir()
{
}