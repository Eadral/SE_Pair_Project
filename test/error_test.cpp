#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(ErrorTest)
	{
	public:

		TEST_METHOD(InvalidInputTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(1
X 0 0 1 1)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)InvalidInput, ret);
		}

		TEST_METHOD(LineLineExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(4
L 0 0 0 1
L 0 0 1 0
L 1 0 1 1
L 0 1 1 1)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}

		TEST_METHOD(LineCircleExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(3
C 0 0 1
L 0 0 1 0
L 0 0 0 1)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}

		TEST_METHOD(CircleCircleExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(3
C 0 0 1
C 1 0 1
C -1 0 1)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}
	};
}
