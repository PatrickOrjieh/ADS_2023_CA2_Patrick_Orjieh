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
    void setLength(std::string length);
    void setType(std::string type);
    ~File();
};
