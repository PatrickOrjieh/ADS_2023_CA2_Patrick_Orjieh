#include "File.h"

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

void File::setLength(std::string length)
{
    this->length = length;
}

void File::setType(std::string type)
{
    this->type = type;
}

File::~File()
{

}