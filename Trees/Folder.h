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
    int count();
    virtual ~Folder() {};
};

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

int Folder::count()
{
	return 1;
}