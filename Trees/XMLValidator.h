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
    size_t pos = 0;
    bool rootFound = false;

    while (pos < xmlContent.size()) {
        if (xmlContent[pos] == '<') {
            size_t end = xmlContent.find('>', pos);
            if (end == std::string::npos) {
                return false; // No closing '>' found for tag
            }

            std::string tag = xmlContent.substr(pos, end - pos + 1);
            if (isTag(tag)) {
                // Check for a closing tag
                if (isClosingTag(tag)) {
                    std::string tagName = getTagName(tag);
                    // Tag mismatch or missing opening tag
                    if (tagsStack.empty() || tagsStack.top() != tagName) {
                        return false;
                    }
                    tagsStack.pop();
                    // The root element is closed properly
                    if (tagsStack.empty()) {
                        rootFound = true;
                    }
                }
                else {
                    // Another root found or invalid tag name
                    if (rootFound || !isValidTagName(getTagName(tag))) {
                        return false;
                    }
                    tagsStack.push(getTagName(tag));
                }
            }
            pos = end + 1;
        }
        else {
            // Increment position if not a tag
            pos++;
        }
    }
    // Validate that all tags were closed and a single root was found
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
    if (tagName.empty() || !isalpha(tagName[0])) {
        return false; // Tag names must start with a letter
    }
    return std::all_of(tagName.begin(), tagName.end(), [](char ch) {
        return isalnum(ch) || ch == '-' || ch == '_' || ch == '.';
        });
}