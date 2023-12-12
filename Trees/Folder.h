#pragma once
#include <string>

class Folder
{
private:
    std::string name;
public:
    Folder(std::string name);
    std::string getName() const;
    void setName(std::string name);
    virtual ~Folder() {};
};


