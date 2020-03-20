#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(ExampleTest)
	{
	public:

		TEST_METHOD(Test1)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
1
L 0 0 1 1
)" << endl;

			solver.Solve();
			
			int ans;
			sout >> ans;

			Assert::AreEqual(0, ans);
		}
		TEST_METHOD(Test2)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
3
L 0 0 1 1
L 1 0 0 1
L 1 2 2 0
)" << endl;

			solver.Solve();

			int ans;
			sout >> ans;

			Assert::AreEqual(3, ans);
		}
		TEST_METHOD(Test3)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
3
L 0 0 1 1
L 0 0 0 1
L 0 0 -1 0
)" << endl;

			solver.Solve();

			int ans;
			sout >> ans;

			Assert::AreEqual(1, ans);
		}
		TEST_METHOD(Test4)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
4
C 1 0 2
C 2 2 1
C 3 -2 6
L -1 4 4 -1
)" << endl;

			solver.Solve();

			int ans;
			sout >> ans;

			Assert::AreEqual(6, ans);
		}
	};
}
