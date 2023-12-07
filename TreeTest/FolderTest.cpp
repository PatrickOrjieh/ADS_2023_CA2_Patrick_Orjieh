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
	};
}