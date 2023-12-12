#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/XMLParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TestXMLParser)
	{
	public:
		XMLParser parser;

		TEST_METHOD(ParseEmptyFile) {
			Tree<Folder*>* tree = parser.parseXML("../../Trees/xml_files/empty.xml");
			Assert::IsNull(tree);
		}

		TEST_METHOD(TestParseXMLWithOneDirectory) {
			Tree<Folder*>* tree = parser.parseXML("../../Trees/xml_files/one_directory.xml");
			Assert::IsNotNull(tree);
			Assert::IsTrue(dynamic_cast<Dir*>(tree->getData()) != nullptr);
			Assert::AreEqual(std::string("RootDir"), tree->getData()->getName());
		}

	};
}