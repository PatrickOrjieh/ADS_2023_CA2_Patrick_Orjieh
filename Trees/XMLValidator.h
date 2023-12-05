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
        return false; // File couldn't be opened
    }

    std::string xmlContent((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    return validate(xmlContent);
}

bool XMLValidator::validate(const std::string& xmlContent) {
    std::stack<std::string> tagsStack;
    size_t pos = 0;
    bool rootFound = false;

    while (pos < xmlContent.size()) {
        if (xmlContent[pos] == '<') {
            // Check for comments
            if (xmlContent.substr(pos, 4) == "<!--") {
                size_t endComment = xmlContent.find("-->", pos);
                if (endComment == std::string::npos) {
                    return false; // Unterminated comment
                }
                pos = endComment + 3;
                continue;
            }
            // Check for CDATA
            else if (xmlContent.substr(pos, 9) == "<![CDATA[") {
                size_t endCDATA = xmlContent.find("]]>", pos);
                if (endCDATA == std::string::npos) {
                    return false; // Unterminated CDATA section
                }
                pos = endCDATA + 3;
                continue;
            }

            size_t end = xmlContent.find('>', pos);
            if (end == std::string::npos) {
                return false; // No closing '>' found for tag
            }

            std::string tag = xmlContent.substr(pos, end - pos + 1);
            if (isTag(tag)) {
                if (isSelfClosingTag(tag)) {
                    // Self-closing tag, do nothing.
                }
                else if (isClosingTag(tag)) {
                    std::string tagName = getTagName(tag);
                    if (tagsStack.empty() || tagsStack.top() != tagName) {
                        return false; // Mismatched or missing opening tag
                    }
                    tagsStack.pop();
                    if (tagsStack.empty()) {
                        rootFound = true; // The root element is closed properly
                    }
                }
                else {
                    if (rootFound) {
                        return false; // Another root found
                    }
                    tagsStack.push(getTagName(tag));
                }
            }
            pos = end + 1;
        }
        else {
            pos++;
        }
    }
    return tagsStack.empty() && rootFound; // If stack is not empty or no root was found, XML is invalid
}


bool XMLValidator::isTag(const std::string& element) {
    return !element.empty() && element.front() == '<' && element.back() == '>';
}

bool XMLValidator::isSelfClosingTag(const std::string& tag) {
    return tag.find("/>") != std::string::npos || (tag.size() >= 3 && tag[tag.size() - 2] == '/');
}

bool XMLValidator::isClosingTag(const std::string& tag) {
    return tag.size() >= 3 && tag[1] == '/';
}

std::string XMLValidator::getTagName(const std::string& tag) {
    size_t start = (tag.front() == '<' && tag[1] == '/') ? 2 : 1;
    size_t end = tag.find_first_of(" />", start);
    return tag.substr(start, end - start);
}