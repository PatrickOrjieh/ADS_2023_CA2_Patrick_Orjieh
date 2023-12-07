#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/Folder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TestFolder)
	{
	public:
		//Test creating a Folder with a given name.
		TEST_METHOD(TestConstructor)
		{
			Folder folder("Folder");
			Assert::AreEqual("Folder", folder.getName().c_str());
		}

	};
}