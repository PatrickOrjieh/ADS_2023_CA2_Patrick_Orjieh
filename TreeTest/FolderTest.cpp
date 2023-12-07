#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/Folder.h"
#include "../Trees/Dir.h"
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
	};
}