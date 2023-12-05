#pragma once
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>


class XMLValidator {
public:
    bool validateFile(const std::string& filename);
private:
    bool validate(const std::string& xmlContent);
    bool isTag(const std::string& element);
    bool isSelfClosingTag(const std::string& tag);
    bool isClosingTag(const std::string& tag);
    std::string getTagName(const std::string& tag);
    bool isValidTagName(const std::string& tagName);
};

bool XMLValidator::validateFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return false;
    }

    // Read the file into a string and close it
    std::string xmlContent((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    return validate(xmlContent);
}

bool XMLValidator::validate(const std::string& xmlContent) {
    std::stack<std::string> tagsStack;
    //set the position to the beginning of the string
    size_t pos = 0;
    bool rootFound = false;

    // Loop through the string until the end is reached
    while (pos < xmlContent.size()) {
        // Check for tag which starts with '<' (position 0)
        if (xmlContent[pos] == '<') {
            // Check for comments
            if (xmlContent.substr(pos, 4) == "<!--") {
                size_t endComment = xmlContent.find("-->", pos);
                //if the endComment is not found, it will return npos
                if (endComment == std::string::npos) {
                    return false;
                }
                // else id found Move the position to the end of the comment
                pos = endComment + 3;
                continue;
            }
            // Check for CDATA
            else if (xmlContent.substr(pos, 9) == "<![CDATA[") {
                size_t endCDATA = xmlContent.find("]]>", pos);
                //same idea as the comment
                if (endCDATA == std::string::npos) {
                    return false;
                }
                pos = endCDATA + 3;
                continue;
            }

            //find the end of the tag if not found return npos
            size_t end = xmlContent.find('>', pos);
            if (end == std::string::npos) {
                return false;
            }

            // Get the tag and check if it is valid
            std::string tag = xmlContent.substr(pos, end - pos + 1);
            if (isTag(tag)) {
                // Check if the tag is self-closing like <tag/> or <tag />
                if (isSelfClosingTag(tag)) {
                    //just continue to the next tag
                }
                else if (isClosingTag(tag)) {
                    std::string tagName = getTagName(tag);
                    // Check if the closing tag matches the top of the stack
                    if (tagsStack.empty() || tagsStack.top() != tagName) {
                        return false;
                    }
                    tagsStack.pop();
                    // Check if the stack is empty, meaning the root element is closed and they ,match
                    if (tagsStack.empty()) {
                        rootFound = true;
                    }
                }
                // If it is not a self-closing or closing tag, it is an opening tag
                else {
                    std::string tagName = getTagName(tag);
                    // Check if the tag name is valid and if the root element was already found
                    if (!isValidTagName(tagName) || rootFound) {
                        return false;
                    }
                    tagsStack.push(tagName);
                }
            }
            // Move the position to the end of the tag (after '>') for the next tag 
            pos = end + 1;
        }
        else {
            // If it is not a tag, move the position to the next character like a space or a letter
            pos++;
        }
    }
    // If stack is not empty or no root was found the XML file is invalid
    return tagsStack.empty() && rootFound;
}

// Check if the string is a tag it should start with '<' and end with '>'
bool XMLValidator::isTag(const std::string& element) {
    return !element.empty() && element.front() == '<' && element.back() == '>';
}

// Check if the tag is self-closing like <tag/> or <tag />
bool XMLValidator::isSelfClosingTag(const std::string& tag) {
    return tag.find("/>") != std::string::npos || (tag.size() >= 3 && tag[tag.size() - 2] == '/');
}

// Check if the tag is a closing tag like </tag>
bool XMLValidator::isClosingTag(const std::string& tag) {
    return tag.size() >= 3 && tag[1] == '/';
}

std::string XMLValidator::getTagName(const std::string& tag) {
    // If it is a closing tag, start from the second character else from the first
    size_t start = (tag.front() == '<' && tag[1] == '/') ? 2 : 1;
    // Find the first space or '>' character
    size_t end = tag.find_first_of(" />", start);
    return tag.substr(start, end - start);
}

bool XMLValidator::isValidTagName(const std::string& tagName) {
    //tags must start with a letter
    if (tagName.empty() || !isalpha(tagName[0])) {
        return false;
    }
    // Check if the rest of the characters are valid
    return std::all_of(tagName.begin(), tagName.end(), [](char ch) {
        return isalnum(ch) || ch == '-' || ch == '_' || ch == '.';
        });
}