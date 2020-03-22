#include "CppUnitTest.h"

#include <sstream>

#include "../src/Core/solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(ErrorAndExceptionTest)
	{
	public:

		TEST_METHOD(InvalidIdentifierTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
1
X 0 0 1 1
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve();});
		}

		TEST_METHOD(NoNTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
L 0 0 1 1
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(WFofNTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
*#06#
L 0 0 1 1
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(WFofDescriptionTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
2
L 0 0 1 1
C 4 3 1 2
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(ExceedCoordinateValTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
2
L 0 0 1 100000
R 4 3 1 2
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(WrongRadiusTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
2
L 0 0 1 1
C 4 2 0
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(InputTooLittleTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
2
L 0 0 1 1
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(InputTooMuchTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			sin << R"(
2
L 0 0 1 1
C 0 2 1
R 1 1 3 4
)" << endl;

			Assert::ExpectException<CoreException>([&] {solver.Solve(); });
		}

		TEST_METHOD(LineLineExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(
4
L 0 0 0 1
L 0 0 1 0
L 1 0 1 1
L 0 1 1 1
)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}

		TEST_METHOD(LineCircleExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(
3
C 0 0 1
L 0 0 1 0
L 0 0 0 1
)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}

		TEST_METHOD(CircleCircleExceedTest)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout, 2);

			sin << R"(
3
C 0 0 1
C 1 0 1
C -1 0 1
)" << endl;

			int ret = solver.Solve();

			Assert::AreEqual((int)MaxPointsExceed, ret);
		}
	};
}
