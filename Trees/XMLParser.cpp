#include "XMLParser.h"

Tree<Folder*>* XMLParser::parseXML(const std::string& filename) {

    std::ifstream file(filename);
    std::string line;
    root = nullptr;

    //this takes each line of the file and puts it into the string line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tag;
        ss >> tag;

        //if the tag is <dir> then we know we have a directory
        if (tag == "<dir>") {
            processDirectory(file);
        }
        else if (tag == "</dir>") {
            //when we reach the end of a directory, we pop it off the stack
            nodeStack.pop();
        }
        else if (tag == "<file>") {
			processFile(file);
		}
    }

    return root;
}

void XMLParser::processDirectory(std::ifstream& file) {
    std::string dirName;
    std::getline(file, dirName);
    //extract the value of the tag
    dirName = extractTagValue(dirName);

    Dir* dir = new Dir(dirName);
    Tree<Folder*>* newNode = new Tree<Folder*>(dir);

    if (nodeStack.empty()) {
        root = newNode;
    }
    else {
        nodeStack.top()->children->append(newNode);
    }
    nodeStack.push(newNode);
}

void XMLParser::processFile(std::ifstream& file) {
    std::string fileName, fileLength, fileType;
    std::getline(file, fileName);
    fileName = extractTagValue(fileName);
    std::getline(file, fileLength);
    fileLength = extractTagValue(fileLength);
    std::getline(file, fileType);
    fileType = extractTagValue(fileType);

    File* fileObj = new File(fileName, fileLength, fileType);
    Tree<Folder*>* newNode = new Tree<Folder*>(fileObj);
    nodeStack.top()->children->append(newNode);
}

std::string XMLParser::extractTagValue(const std::string& line) {
    //find the first > and the first < after that
    //the substring between those two is the value of the tag
    size_t start = line.find('>') + 1;
    size_t end = line.find('<', start);
    return line.substr(start, end - start);
}