#pragma once
#include <string>
#include <stack>
#include <fstream>

class XMLValidator {
public:
    bool validateFile(const std::string& filename);
private:
    bool validate(const std::string& xmlContent);
    bool isTag(const std::string& element);
    bool isSelfClosingTag(const std::string& tag);
    bool isClosingTag(const std::string& tag);
    std::string getTagName(const std::string& tag);
    bool isCommentOrCDATA(const std::string& tag);
    bool isValidTagName(const std::string& tagName);
};

bool XMLValidator::validateFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Read the file into a string and close the file
    std::string xmlContent((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    return validate(xmlContent);
}

bool XMLValidator::validate(const std::string& xmlContent) {
    std::stack<std::string> tagsStack;
    // to keep track of the tags that are opened but not closed yet
    size_t pos = 0;
    bool rootFound = false;

    // Iterate over the string and find tags
    while (pos < xmlContent.size()) {
        // If '<' is found, it is a tag
        if (xmlContent[pos] == '<') {
            size_t end = xmlContent.find('>', pos);
            // If '>' is not found, the XML is invalid
            if (end == std::string::npos) {
                return false; // No closing '>' found for tag
            }

            // Extract the tag
            std::string tag = xmlContent.substr(pos, end - pos + 1);
            if (isTag(tag)) {
                if (isClosingTag(tag)) {
                    std::string tagName = getTagName(tag);
                    if (tagsStack.empty() || tagsStack.top() != tagName) {
                        // Mismatched or missing opening tag
                        return false;
                    }
                    tagsStack.pop();
                    if (tagsStack.empty()) {
                        // The root element is closed properly
                        rootFound = true;
                    }
                }
                else {
                    if (rootFound) {
                        // Another root found, which is invalid
                        return false;
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
    // If stack is not empty or no root was found, XML is invalid
    return tagsStack.empty() && rootFound;
}

bool XMLValidator::isTag(const std::string& element) {
    return !element.empty() && element.front() == '<' && element.back() == '>';
}

bool XMLValidator::isClosingTag(const std::string& tag) {
    return tag.size() >= 3 && tag[1] == '/';
}

std::string XMLValidator::getTagName(const std::string& tag) {
    size_t start = tag.front() == '<' && tag[1] == '/' ? 2 : 1;
    size_t end = tag.find('>', start);
    return tag.substr(start, end - start);
}

bool XMLValidator::isSelfClosingTag(const std::string& tag) {
	return false;
}

bool XMLValidator::isCommentOrCDATA(const std::string& tag) {
	return false;
}

bool XMLValidator::isValidTagName(const std::string& tagName) {
	return false;
}