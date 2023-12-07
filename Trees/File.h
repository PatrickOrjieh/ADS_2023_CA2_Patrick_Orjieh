#pragma once
#include "Folder.h"
#include <string>

class File : public Folder
{
private:
    std::string length;
    std::string type;
public:
    File(std::string name, std::string length, std::string type);
    std::string getLength();
    std::string getType();
    ~File();
};

File::File(std::string name, std::string length, std::string type) : Folder(name)
{
    this->length = length;
    this->type = type;
}

std::string File::getLength()
{
    return length;
}

std::string File::getType()
{
    return type;
}

File::~File()
{

}