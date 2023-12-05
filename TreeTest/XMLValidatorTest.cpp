#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/XMLValidator.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TestXMLValidator)
	{
	public:
        XMLValidator validator;

        TEST_METHOD(TestMethod_ValidateEmptyFile) {
            Assert::IsFalse(validator.validateFile("empty.xml"), L"An empty XML should be invalid.");
        }

        TEST_METHOD(TestMethod_ValidateSimpleValidXMLFile) {
            Assert::IsTrue(validator.validateFile("simple_valid.xml"), L"A simple valid XML with a single root should be valid.");
        }

        TEST_METHOD(TestMethod_ValidateNestedValidXMLFile) {
            Assert::IsTrue(validator.validateFile("nested_valid.xml"), L"A nested valid XML should be valid.");
        }
	};
}