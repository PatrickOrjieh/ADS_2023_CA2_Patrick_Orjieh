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
            File* file1 = new File("File1", "100b", "text/plain");
            File* file2 = new File("File2", "200b", "text/plain");

            Tree<Folder*>* fileNode1 = new Tree<Folder*>(file1);
            Tree<Folder*>* fileNode2 = new Tree<Folder*>(file2);

            Dir* rootDir = new Dir("RootDir");

            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            rootNode->children->append(fileNode1);
            rootNode->children->append(fileNode2);

            fileNode1->parent = rootNode;
            fileNode2->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

            Assert::AreEqual(2, itemCount, L"Folder with 2 files should have 2 items.");
        }

        TEST_METHOD(TestCountItemsInFolderWithDirectories)
        {
            Dir* dir1 = new Dir("Dir1");
            Dir* dir2 = new Dir("Dir2");

            Tree<Folder*>* dirNode1 = new Tree<Folder*>(dir1);
            Tree<Folder*>* dirNode2 = new Tree<Folder*>(dir2);

            Dir *rootDir = new Dir("RootDir");

            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            rootNode->children->append(dirNode1);
            rootNode->children->append(dirNode2);

            dirNode1->parent = rootNode;
            dirNode2->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

            Assert::AreEqual(2, itemCount, L"Folder with 2 directories should have 2 items.");
        }

        TEST_METHOD(TestCountItemsInFolderWithFilesAndDirectories)
        {
            File* file1 = new File("File1", "100b", "text/plain");
            File* file2 = new File("File2", "200b", "text/plain");

            Tree<Folder*>* fileNode1 = new Tree<Folder*>(file1);
            Tree<Folder*>* fileNode2 = new Tree<Folder*>(file2);

            Dir* rootDir = new Dir("RootDir");

            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            rootNode->children->append(fileNode1);
            rootNode->children->append(fileNode2);

            fileNode1->parent = rootNode;
            fileNode2->parent = rootNode;

            // add a dir with no files
            Dir* dir1 = new Dir("Dir1");

            Tree<Folder*>* dirNode1 = new Tree<Folder*>(dir1);

            rootNode->children->append(dirNode1);

            dirNode1->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

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

        TEST_METHOD(TestPruneEmptyFolders) {
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

            // add a dir with no files
            Dir* dir2 = new Dir("Dir2");

            Tree<Folder*>* dirNode2 = new Tree<Folder*>(dir2);

            rootNode->children->append(dirNode2);

            dirNode2->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            TreeUtilities::pruneEmptyDirectories(rootNode);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

            Assert::AreEqual(1, itemCount, L"Prune empty folders should remove the empty folder.");
		}

        TEST_METHOD(TestPruneEmptyFoldersWithMultipleEmptyFolders) {
            Dir* rootDir = new Dir("RootDir");
            Tree<Folder*>* rootNode = new Tree<Folder*>(rootDir);

            Dir* dir1 = new Dir("Dir1");
            Tree<Folder*>* dirNode1 = new Tree<Folder*>(dir1);

            Dir* dir2 = new Dir("Dir2");
            Tree<Folder*>* dirNode2 = new Tree<Folder*>(dir2);

            rootNode->children->append(dirNode1);
            rootNode->children->append(dirNode2);

            dirNode1->parent = rootNode;
            dirNode2->parent = rootNode;

            TreeIterator<Folder*> iter(rootNode);

            TreeUtilities::pruneEmptyDirectories(rootNode);

            int itemCount = TreeUtilities::countItemsInFolder(iter);

            Assert::AreEqual(0, itemCount, L"Prune empty folders should remove all the subfolders.");
        }

        TEST_METHOD(TestFindPath) {
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

			std::string path = TreeUtilities::findPath(iter, "File1");

			Assert::AreEqual(std::string("RootDir/Dir1/File1"), path, L"Path to File1 should be RootDir/Dir1/File1.");
		}

        TEST_METHOD(TestFindPathWithPartialName) {
            File *file1 = new File("resume", "100b", "text/plain");
            File *file2 = new File("File2", "0b", "text/plain");

            Tree<Folder *> *fileNode1 = new Tree<Folder *>(file1);
            Tree<Folder *> *fileNode2 = new Tree<Folder *>(file2);

            Dir *dir1 = new Dir("Dir1");
            Tree<Folder *> *dirNode1 = new Tree<Folder *>(dir1);

            dirNode1->children->append(fileNode1);
            dirNode1->children->append(fileNode2);

            fileNode1->parent = dirNode1;
            fileNode2->parent = dirNode1;

            Dir *rootDir = new Dir("RootDir");

            Tree<Folder *> *rootNode = new Tree<Folder *>(rootDir);

            rootNode->children->append(dirNode1);

            dirNode1->parent = rootNode;

            TreeIterator<Folder *> iter(rootNode);

            std::string path = TreeUtilities::findPath(iter, "res");

            Assert::AreEqual(std::string("RootDir/Dir1/resume"), path, L"Path to resume should be RootDir/Dir1/resume.");
        }

        TEST_METHOD(TestFindPathWithNoMatch) {
			File *file1 = new File("resume", "100b", "text/plain");
			File *file2 = new File("File2", "0b", "text/plain");

			Tree<Folder *> *fileNode1 = new Tree<Folder *>(file1);
			Tree<Folder *> *fileNode2 = new Tree<Folder *>(file2);

			Dir *dir1 = new Dir("Dir1");
			Tree<Folder *> *dirNode1 = new Tree<Folder *>(dir1);

			dirNode1->children->append(fileNode1);
			dirNode1->children->append(fileNode2);

			fileNode1->parent = dirNode1;
			fileNode2->parent = dirNode1;

			Dir *rootDir = new Dir("RootDir");

			Tree<Folder *> *rootNode = new Tree<Folder *>(rootDir);

			rootNode->children->append(dirNode1);

			dirNode1->parent = rootNode;

			TreeIterator<Folder *> iter(rootNode);

			std::string path = TreeUtilities::findPath(iter, "resumes");

			Assert::AreEqual(std::string(""), path, L"Path to resume should be empty.");
		}
    };
}
