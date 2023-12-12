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

		TEST_METHOD(TestParseXMLWithOneFile) {
			XMLParser parser;
			Tree<Folder*>* tree = parser.parseXML("../../Trees/xml_files/one_file.xml");
			Assert::IsNotNull(tree);
			Assert::IsTrue(dynamic_cast<Dir*>(tree->getData()) != nullptr);
			Assert::AreEqual(std::string("MainDirectory"), tree->getData()->getName());
			DListIterator<Tree<Folder*>*> iter = tree->children->getIterator();
			Assert::IsTrue(iter.isValid());
			File* fileChild = dynamic_cast<File*>(iter.item()->getData());
			Assert::IsNotNull(fileChild);
			Assert::AreEqual(std::string("Document.txt"), fileChild->getName());
			Assert::AreEqual(std::string("1024b"), fileChild->getLength());
			Assert::AreEqual(std::string("text/plain"), fileChild->getType());
		}

	};
}