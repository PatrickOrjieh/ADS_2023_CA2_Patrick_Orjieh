#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/XMLValidator.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TestXMLValidator)
	{
	public:
        XMLValidator validator;

        TEST_METHOD(TestMethod_ValidateEmptyFile) {
            //initially tried using the relative path and was giving me an error
            //so  i used this current path to get the path of the project
            std::string currentPath = fs::current_path().string();
            Logger::WriteMessage(("Current Path: " + currentPath).c_str());

            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/empty.xml"), L"An empty XML should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateSimpleValidXMLFile) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/simple_valid.xml"), L"A simple valid XML with a single root should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateNestedValidXMLFile) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/nested_valid.xml"), L"A nested valid XML should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithContentFile) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/content_valid.xml"), L"XML with content inside tags should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithMismatchedTagsFile) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/mismatched_tags.xml"), L"XML with mismatched tags should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithoutRoot) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/no_root.xml"), L"XML without a single root element should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithMultipleRoots) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/multiple_roots.xml"), L"XML with multiple root elements should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithUnclosedTag) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/unclosed_tag.xml"), L"XML with an unclosed tag should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithExtraClosingTag) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/extra_closing_tag.xml"), L"XML with an extra closing tag should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithOverlappingTags) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/overlapping_tags.xml"), L"XML with overlapping tags should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithSelfClosingTag) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/self_closing_tag.xml"), L"XML with self-closing tags should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithComments) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/comments.xml"), L"XML with comments should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithCDATA) {
            Assert::IsTrue(validator.validateFile("../../Trees/xml_files/cdata.xml"), L"XML with CDATA section should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateXMLWithSpecialCharactersInTags) {
            Assert::IsFalse(validator.validateFile("../../Trees/xml_files/special_chars_in_tags.xml"), L"XML with special characters in tag names should be valid.");
        }
	};
}