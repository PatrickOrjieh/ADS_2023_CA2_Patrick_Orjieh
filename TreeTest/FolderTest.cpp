#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/Folder.h"
#include "../Trees/Dir.h"
#include "../Trees/Tree.h"
#include "../Trees/File.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TestFolder)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			Folder folder("Folder");
			Assert::AreEqual("Folder", folder.getName().c_str());
		}

		TEST_METHOD(TestSetName)
		{
			Folder folder("Folder");
			folder.setName("New Folder");
			Assert::AreEqual("New Folder", folder.getName().c_str());
		}

		TEST_METHOD(TestDirConstructor)
		{
			Dir dir("Dir");
			Assert::AreEqual("Dir", dir.getName().c_str());
		}

		TEST_METHOD(TestDirSetName)
		{
			Dir dir("Dir");
			dir.setName("New Dir");
			Assert::AreEqual("New Dir", dir.getName().c_str());
		}

		TEST_METHOD(TestDirCountEmpty)
		{
			Dir dir("Dir");
			Assert::AreEqual(0, dir.count());
		}

		TEST_METHOD(TestAddSubdirectoryAndCount)
		{
			Dir mainDir("MainDir");

			Assert::AreEqual(0, mainDir.count(), L"Initial count should be zero.");

			Dir* subDir = new Dir("SubDir");
			Tree<Folder*>* subDirTree = new Tree<Folder*>(subDir);
			mainDir.addChild(subDirTree);

			Assert::AreEqual(1, mainDir.count(), L"Count after adding subdirectory should be one.");
		}

		TEST_METHOD(TestFileConstructor)
		{
			File file("File", "10", "txt");
			Assert::AreEqual("File", file.getName().c_str());
			Assert::AreEqual("10", file.getLength().c_str());
			Assert::AreEqual("txt", file.getType().c_str());
		}

		TEST_METHOD(TestFileSetMethods)
		{
			File file("File", "10", "txt");
			file.setName("New File");
			Assert::AreEqual("New File", file.getName().c_str());
			file.setLength("20");
			Assert::AreEqual("20", file.getLength().c_str());
			file.setType("doc");
			Assert::AreEqual("20", file.getLength().c_str());
		}

		TEST_METHOD(TestAddFileAndCount)
		{
			Dir mainDir("MainDir");

			Assert::AreEqual(0, mainDir.count(), L"Initial count should be zero.");

			File* file = new File("File", "10", "txt");
			Tree<Folder*>* fileTree = new Tree<Folder*>(file);
			mainDir.addChild(fileTree);

			Assert::AreEqual(1, mainDir.count(), L"Count after adding file should be one.");
		}

		TEST_METHOD(TestAddFilesAndSubdirectoriesAndCount)
		{
			Dir mainDir("MainDir");

			Assert::AreEqual(0, mainDir.count(), L"Initial count should be zero.");

			File* file1 = new File("File1", "10", "txt");
			Tree<Folder*>* fileTree1 = new Tree<Folder*>(file1);
			mainDir.addChild(fileTree1);

			File* file2 = new File("File2", "10", "txt");
			Tree<Folder*>* fileTree2 = new Tree<Folder*>(file2);
			mainDir.addChild(fileTree2);

			File* file3 = new File("File3", "10", "txt");
			Tree<Folder*>* fileTree3 = new Tree<Folder*>(file3);
			mainDir.addChild(fileTree3);

			Assert::AreEqual(3, mainDir.count(), L"Count after adding three files should be three.");

			Dir* subDir1 = new Dir("SubDir1");
			Tree<Folder*>* subDirTree1 = new Tree<Folder*>(subDir1);
			mainDir.addChild(subDirTree1);

			Dir* subDir2 = new Dir("SubDir2");
			Tree<Folder*>* subDirTree2 = new Tree<Folder*>(subDir2);
			mainDir.addChild(subDirTree2);

			Assert::AreEqual(5, mainDir.count(), L"Count after adding files and subdirectories should be five.");
		}
	};
}