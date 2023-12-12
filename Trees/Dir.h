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