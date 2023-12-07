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
    int size();
    ~Dir();
};

Dir::Dir(std::string name) : Folder(name)
{
	children = new DList<Tree<Folder*>*>(); 
}

int Dir::size()
{
	int size = 0;
	return size;
}

Dir::~Dir()
{
}