#pragma once
#include <string>
#include <stack>
#include "Tree.h"
#include "Dir.h"
#include "File.h"
#include <fstream>
#include <sstream>

class XMLParser
{
public:
    Tree<Folder*>* parseXML(const std::string& filename);

private:
    Tree<Folder*>* root;
    std::stack<Tree<Folder*>*> nodeStack;
    void processDirectory(std::ifstream& file);
    void processFile(std::ifstream& file);
    std::string extractTagValue(const std::string& line);
};

