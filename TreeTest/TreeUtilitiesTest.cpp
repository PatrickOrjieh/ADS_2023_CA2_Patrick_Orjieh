#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/TreeUtilities.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileManagerTest
{
    TEST_CLASS(TreeUtilitiesTest)
    {
    public:

        TEST_METHOD(TestCountItemsInEmptyFolder)
        {
            Dir rootDir("Root");
            Tree<Folder*> tree(&rootDir);
            TreeIterator<Folder*> iter(&tree);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

            Assert::AreEqual(0, itemCount, L"Empty folder should have 0 items.");
        }

        TEST_METHOD(TestCountItemsInFolderWithFiles)
        {
            Dir rootDir("Root");
            Tree<Folder*> tree(&rootDir);
            rootDir.addChild(new Tree<Folder*>(new File("File1", "100b", "text/plain")));
            rootDir.addChild(new Tree<Folder*>(new File("File2", "200b", "text/plain")));
            TreeIterator<Folder*> iter(&tree);

            int itemCount = rootDir.count();

            Assert::AreEqual(2, itemCount, L"Folder with 2 files should have 2 items.");
        }

        TEST_METHOD(TestCountItemsInFolderWithDirectories)
        {
            Dir rootDir("Root");
			Tree<Folder*> tree(&rootDir);
			rootDir.addChild(new Tree<Folder*>(new Dir("Dir1")));
			rootDir.addChild(new Tree<Folder*>(new Dir("Dir2")));
			TreeIterator<Folder*> iter(&tree);

			int itemCount = rootDir.count();

			Assert::AreEqual(2, itemCount, L"Folder with 2 directories should have 2 items.");
        }

        TEST_METHOD(TestCountItemsInFolderWithFilesAndDirectories)
        {
            Dir rootDir("Root");
            Tree<Folder*> tree(&rootDir);
            rootDir.addChild(new Tree<Folder*>(new File("File1", "100b", "text/plain")));
            rootDir.addChild(new Tree<Folder*>(new Dir("Dir1")));
            rootDir.addChild(new Tree<Folder*>(new File("File2", "200b", "text/plain")));

            TreeIterator<Folder*> iter(&tree);
            
            int itemCount = rootDir.count();

            Assert::AreEqual(3, itemCount, L"Folder with 2 files and 1 directory should have 3 items.");
        }
    };
}
