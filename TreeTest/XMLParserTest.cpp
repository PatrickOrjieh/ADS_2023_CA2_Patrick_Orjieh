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
	};
}