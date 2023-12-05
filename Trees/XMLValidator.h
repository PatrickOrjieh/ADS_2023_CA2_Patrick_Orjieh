#pragma once
#include <string>
#include <stack>

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