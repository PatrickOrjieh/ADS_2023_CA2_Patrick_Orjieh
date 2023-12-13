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

        TEST_METHOD(TestMemoryUsedBySingleFolder) {
            File* file1 = new File("File1", "100b", "text/plain");
            File* file2 = new File("File2", "200b", "text/plain");
            File* file3 = new File("File3", "300b", "text/plain");

            Tree<Folder*>* fileNode1 = new Tree<Folder*>(file1);
            Tree<Folder*>* fileNode2 = new Tree<Folder*>(file2);
            Tree<Folder*>* fileNode3 = new Tree<Folder*>(file3);

            Dir* rootDir = new Dir("RootDir");

            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            rootNode->children->append(fileNode1);
            rootNode->children->append(fileNode2);
            rootNode->children->append(fileNode3);

            fileNode1->parent = rootNode;
            fileNode2->parent = rootNode;
            fileNode3->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            double totalMemory = TreeUtilities::memoryUsed(iter);

            Assert::AreEqual(600.00, totalMemory, 0.01, L"Memory used by folder with 3 files should be 600 bytes.");

            delete rootNode;
        }

        TEST_METHOD(TestMemoryUsedByFolderWithFilesAndDirectories) {
			File* file1 = new File("File1", "100b", "text/plain");
			File* file2 = new File("File2", "0b", "text/plain");

            Tree<Folder*>* fileNode1 = new Tree<Folder*>(file1);
            Tree<Folder*>* fileNode2 = new Tree<Folder*>(file2);

            Dir* dir1 = new Dir("Dir1");
            Tree<Folder*>* dirNode1 = new Tree<Folder*>(dir1);

            dirNode1->children->append(fileNode1);
            dirNode1->children->append(fileNode2);

            fileNode1->parent = dirNode1;
            fileNode2->parent = dirNode1;

            Dir* rootDir = new Dir("RootDir");
            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            rootNode->children->append(dirNode1);

            dirNode1->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            double totalMemory = TreeUtilities::memoryUsed(iter);

            Assert::AreEqual(100.00, totalMemory, 0.01, L"Memory used by folder with 2 files should be 100 bytes.");
		}


    };
}
