#pragma once
#include <string>

class Folder
{
private:
    std::string name;
public:
    Folder(std::string name);
    std::string getName();
};

Folder::Folder(std::string name)
{
    this->name = name;
}

std::string Folder::getName()
{
    return name;
}