#include "Folder.h"

Folder::Folder(std::string name)
{
    this->name = name;
}

std::string Folder::getName() const
{
    return name;
}

void Folder::setName(std::string name)
{
    this->name = name;
}
