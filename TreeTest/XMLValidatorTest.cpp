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
	};
}