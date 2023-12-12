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

        TEST_METHOD(TestParseNestedDirectories) {
            Tree<Folder*>* tree = parser.parseXML("../../Trees/xml_files/nested_directories.xml");
            Assert::IsNotNull(tree);

            Assert::IsTrue(dynamic_cast<Dir*>(tree->getData()) != nullptr);
            Assert::AreEqual(std::string("RootDir"), tree->getData()->getName());

			// Navigate to SubDir1
			DListIterator<Tree<Folder*>*> iter = tree->children->getIterator();
			Assert::IsTrue(iter.isValid());
			Dir* subDir1 = dynamic_cast<Dir*>(iter.item()->getData());
			Assert::IsNotNull(subDir1);
			Assert::AreEqual(std::string("SubDir1"), subDir1->getName());

			// Check file in SubDir1
			DListIterator<Tree<Folder*>*> subDir1Iter = iter.item()->children->getIterator();
			File* file1 = dynamic_cast<File*>(subDir1Iter.item()->getData());
			Assert::IsNotNull(file1);
			Assert::AreEqual(std::string("File1.txt"), file1->getName());
			Assert::AreEqual(std::string("500b"), file1->getLength());
			Assert::AreEqual(std::string("text/plain"), file1->getType());

			// Navigate to SubDir2 and InnerDir
			iter.advance();
			Dir* subDir2 = dynamic_cast<Dir*>(iter.item()->getData());
			Assert::IsNotNull(subDir2);
			DListIterator<Tree<Folder*>*> innerDirIter = iter.item()->children->getIterator();
			Dir* innerDir = dynamic_cast<Dir*>(innerDirIter.item()->getData());
			Assert::IsNotNull(innerDir);

			// Check file in InnerDir
			DListIterator<Tree<Folder*>*> fileIter = innerDirIter.item()->children->getIterator();
			File* file2 = dynamic_cast<File*>(fileIter.item()->getData());
			Assert::IsNotNull(file2);
			Assert::AreEqual(std::string("Image.png"), file2->getName());
			Assert::AreEqual(std::string("2Mb"), file2->getLength());
			Assert::AreEqual(std::string("image/png"), file2->getType());
        }
	};
}