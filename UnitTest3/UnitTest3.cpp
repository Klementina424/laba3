#include "pch.h"
#include "CppUnitTest.h"
#include "../Dijkstra/list.h"
#include <string>
#include "../Dijkstra/someFunction.h"
#include "../Dijkstra/Cities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest3
{
	TEST_CLASS(UnitTest3)
	{
	public:
		
		TEST_METHOD(setFunction_test)
		{
			List<string> list;
			string str;
			list.push("one");
			list.push("two");
			list.push("thee");
			str = ("two");
			bool flag = setFunction(list, str);
			Assert::IsTrue(flag);
		}

		TEST_METHOD(isAllVisited_test)
		{
			CityNode* node = new CityNode[5];
			for (int i = 0; i < 5; i++) 
			{
				node[i].isVisited = true;
			}
			Assert::IsTrue(isAllVisited(node, 5));
		}
		
		TEST_METHOD(PushBack_test)
		{
			List<int> list;
			list.push(1);
			list.push(2);
			list.push(3);
			list.push(4);
			Assert::IsTrue(list[2] == 3);
		}

		TEST_METHOD(PopFront_test)
		{
			List<int> list;
			list.push(1);
			list.push(2);
			list.push(3);
			list.push(4);
			list.pop();
			Assert::IsTrue(list[2] == 3);
		}

	};
}
